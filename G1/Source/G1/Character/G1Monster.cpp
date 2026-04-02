// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/G1Monster.h"
#include "AbilitySystem/Attributes/G1MonsterSet.h"
#include "AbilitySystem/G1AbilitySystem.h"
#include "Components/BoxComponent.h"
#include "Character/G1Player.h"
#include "Item/G1EquipmentItem.h"
#include "Animation/AnimMontage.h"
#include "System/G1AssetManager.h"
#include "Item/G1DropItem.h"
#include "Data/G1DropTableData.h"

AG1Monster::AG1Monster()
	: Super()
{
	TeamTag = G1GameplayTags::Team_Monster;

	GetMesh()->SetRelativeLocationAndRotation(FVector(0.f, 0.f, -88.f), FRotator(0.f, -90.f, 0.f));

	AbilitySystem = CreateDefaultSubobject<UG1AbilitySystem>("AbilitySystem");

	AttributeSet = CreateDefaultSubobject<UG1MonsterSet>("MonsterSet");

	//RHandHitBox = Cast<UBoxComponent>(GetDefaultSubobjectByName(TEXT("R_Hand_HitBox")));
	//RHandHitBox->OnComponentBeginOverlap.AddDynamic(this, &AG1Monster::OnAttackOverlap);

	//LHandHitBox = Cast<UBoxComponent>(GetDefaultSubobjectByName(TEXT("L_Hand_HitBox")));
	//LHandHitBox->OnComponentBeginOverlap.AddDynamic(this, &AG1Monster::OnAttackOverlap);



	/*RHandHitBox = CreateDefaultSubobject<UBoxComponent>(TEXT("RHandHitBox"));
	RHandHitBox->SetupAttachment(GetMesh(), TEXT("hand_r"));
	RHandHitBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RHandHitBox->OnComponentBeginOverlap.AddDynamic(this, &AG1Monster::OnAttackOverlap);

	LHandHitBox = CreateDefaultSubobject<UBoxComponent>(TEXT("LHandHitBox"));
	LHandHitBox->SetupAttachment(GetMesh(), TEXT("hand_l"));
	LHandHitBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	LHandHitBox->OnComponentBeginOverlap.AddDynamic(this, &AG1Monster::OnAttackOverlap);*/

	//RHandHitBox->SetupAttachment(GetMesh(), TEXT("RightHandSocket"));
	//RHandHitBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	//RHandHitBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	//RHandHitBox->SetCollisionObjectType(ECC_WorldDynamic);
	//RHandHitBox->SetCollisionResponseToAllChannels(ECR_Ignore);
	//RHandHitBox->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
}

void AG1Monster::OnAttackOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	/*if (OtherActor->Implements<Interface>())
	{

	}*/
	AG1Player* demagedPlayer = Cast<AG1Player>(OtherActor);
	if (demagedPlayer == nullptr || demagedPlayer->State == ECharacterState::Dead)
	{
		return;
	}

	if (OverlappedComponent == RHandHitBox || OverlappedComponent == LHandHitBox)
	{
		demagedPlayer->OnDamaged(AttributeSet->GetBaseDamage(), Cast<AG1Character>(this), SweepResult);
	}
}

void AG1Monster::BeginPlay()
{
	Super::BeginPlay();

	InitAbilitySystem();

	/*TArray<UBoxComponent*> Boxes;
	GetComponents<UBoxComponent>(Boxes);

	for (UBoxComponent* Box : Boxes)
	{
		if (Box->GetName() == TEXT("R_Hand_HitBox"))
		{
			RHandHitBox = Box;
			RHandHitBox->OnComponentBeginOverlap.AddDynamic(this, &AG1Monster::OnAttackOverlap);
			RHandHitBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		}
		else if (Box->GetName() == TEXT("L_Hand_HitBox"))
		{
			LHandHitBox = Box;
			LHandHitBox->OnComponentBeginOverlap.AddDynamic(this, &AG1Monster::OnAttackOverlap);
			LHandHitBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		}
	}*/
}

void AG1Monster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AG1Monster::InitAbilitySystem()
{
	Super::InitAbilitySystem();

	AbilitySystem->InitAbilityActorInfo(this, this);
}

void AG1Monster::HandleGameplayEvent(UAnimMontage* Montage, FGameplayTag EventTag, ECharacterAnimNotiType EventType)
{
	Super::HandleGameplayEvent(Montage, EventTag, EventType);
}

void AG1Monster::OnDead(TObjectPtr<AG1Character> Attacker)
{
	Super::OnDead(Attacker);

	if (const UG1DropTableData* DropData = UG1AssetManager::GetAssetByName<UG1DropTableData>("MonsterDropData"))
	{
		const UG1ItemData* ItemData = UG1AssetManager::GetAssetByName<UG1ItemData>("Item_Weapon");
		if (ItemData == nullptr)
		{
			return;
		}

		TArray<FG1DropResult> Drops;
		DropData->RollDrops(MonsterDropID, Drops);
		for (const FG1DropResult& R : Drops)
		{
			if (const FG1ItemInfo* Info = ItemData->FindItemInfo(R.ItemID))
			{
				UWorld* World = GetWorld();
				if (!World) continue;

				FVector SpawnLoc = GetActorLocation(); // + 오프셋
				FRotator SpawnRot = FRotator::ZeroRotator;

				// 우선 DropActorClass 우선 사용
				if (IsValid(Info->DropStaticMeshClass))
				{
					AG1DropItem* DropItem = World->SpawnActor<AG1DropItem>(Info->DropStaticMeshClass);
					if (IsValid(DropItem) && IsValid(GetMesh()))
					{

					}
				}
			}
		}
	}
}
