// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/G1EquipmentItem.h"
#include "Character/G1Character.h"
#include "Components/BoxComponent.h"

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

}

void AG1EquipmentItem::SetOwner(AG1Character* owner)
{
	ownerCharacter = owner;
}

void AG1EquipmentItem::SetWeaponCollisionEnabled(bool Enabled)
{
	if (CollisionBox)
	{
		CollisionBox->SetCollisionEnabled(Enabled ? ECollisionEnabled::QueryOnly : ECollisionEnabled::NoCollision);
	}
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
