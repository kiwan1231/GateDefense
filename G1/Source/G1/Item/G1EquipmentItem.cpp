// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/G1EquipmentItem.h"
#include "Character/G1Character.h"
#include "Components/BoxComponent.h"
#include "Data/G1ItemData.h"

// Sets default values
AG1EquipmentItem::AG1EquipmentItem()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AG1EquipmentItem::BeginPlay()
{
	Super::BeginPlay();

	TArray<UBoxComponent*> Boxes;
	GetComponents<UBoxComponent>(Boxes);

	for (UBoxComponent* Box : Boxes)
	{
		if (Box->GetName() == TEXT("WeaponCollisionBox"))
		{
			CollisionBox = Box;
			CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &AG1EquipmentItem::OnAttackOverlap);
			CollisionBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		}
	}
}

// Called every frame
void AG1EquipmentItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    if (bIsAttacking)
    {
        PerformAttackTrace();
    }
}

void AG1EquipmentItem::InitEquipment(FName _ItemID)
{
	ItemID = _ItemID;
}

void AG1EquipmentItem::EquipItemSetOwner(AG1Character* owner)
{
	ownerCharacter = owner;
}

void AG1EquipmentItem::SetWeaponCollisionEnabled(bool Enabled)
{
	HitActors.Empty();
    bIsAttacking = Enabled;

	/*if (CollisionBox)
	{
		CollisionBox->SetGenerateOverlapEvents(true);
		CollisionBox->SetCollisionEnabled(Enabled ? ECollisionEnabled::QueryOnly : ECollisionEnabled::NoCollision);
	}*/
}

void AG1EquipmentItem::OnAttackOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (ownerCharacter.IsValid() == false)
	{
		return;
	}

	AG1Character* demagedPlayer = Cast<AG1Character>(OtherActor);
	if (demagedPlayer == nullptr 
		|| demagedPlayer->State == ECharacterState::Dead
		|| ownerCharacter->IsEnemyTeam(OtherActor) == false)
	{
		return;
	}

	if (OverlappedComponent == CollisionBox)
	{
		demagedPlayer->OnDamaged(ownerCharacter->TotalDemage(), Cast<AG1Character>(ownerCharacter), SweepResult);
	}
}

void AG1EquipmentItem::PerformAttackTrace()
{
    if (!CollisionBox) return;

    FVector CurrentLocation = CollisionBox->GetComponentLocation();
    FQuat   CurrentRotation = CollisionBox->GetComponentQuat();

    // 첫 프레임 초기화
    if (PrevLocation.IsZero())
    {
        PrevLocation = CurrentLocation;
        PrevRotation = CurrentRotation;
        return;
    }

    TArray<FHitResult> HitResults;

    FCollisionQueryParams Params;
    Params.AddIgnoredActor(ownerCharacter.Get());

    FVector BoxExtent = CollisionBox->GetScaledBoxExtent();

    bool bHit = GetWorld()->SweepMultiByChannel(
        HitResults,
        PrevLocation,
        CurrentLocation,
        CurrentRotation,
        ECC_Pawn,
        FCollisionShape::MakeBox(BoxExtent),
        Params
    );

    if (bHit)
    {
        for (auto& Hit : HitResults)
        {
            AActor* HitActor = Hit.GetActor();

            if (!HitActor) continue;
            if (HitActors.Contains(HitActor)) continue;

            AG1Character* Damaged = Cast<AG1Character>(HitActor);
            if (!Damaged) continue;

            if (Damaged->State == ECharacterState::Dead) continue;
            if (!ownerCharacter->IsEnemyTeam(HitActor)) continue;

            Damaged->OnDamaged(
                ownerCharacter->TotalDemage(),
                Cast<AG1Character>(ownerCharacter),
                Hit
            );

            HitActors.Add(HitActor);
        }
    }

    // 디버그 (박스 이동 경로)
    //DrawDebugBox(GetWorld(), CurrentLocation, BoxExtent, CurrentRotation, FColor::Red, false, 0.1f);

    PrevLocation = CurrentLocation;
    PrevRotation = CurrentRotation;
}
