// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/G1Character.h"
#include "AbilitySystem/G1AbilitySystem.h"
#include "AbilitySystem/Attributes/G1AttributeSet.h"
#include "Utility/G1CharacterDefine.h"
#include "System/G1AssetManager.h"
#include "Data/G1ItemData.h"
#include "Item/G1EquipmentItem.h"
#include "Components/SceneComponent.h"
#include "Engine/EngineTypes.h"
#include "Utility/G1GameplayTags.h"

// Sets default values
AG1Character::AG1Character()
	: Super()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TeamTag = G1GameplayTags::Team_None;
}

// Called when the game starts or when spawned
void AG1Character::BeginPlay()
{
	Super::BeginPlay();
	
	AddCharacterAbilities();

	InitEquipment();
}

// Called every frame
void AG1Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
void AG1Character::HandleGameplayEvent(FGameplayTag EventTag, ECharacterAnimNotiType EventType)
{
	
}

// Called to bind functionality to input
void AG1Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

UAbilitySystemComponent* AG1Character::GetAbilitySystemComponent() const
{
	return AbilitySystem;
}

void AG1Character::OnDamaged(int32 Damage, TObjectPtr<AG1Character> Attacker)
{
	float Hp = AttributeSet->GetHealth();
	float MaxHp = AttributeSet->GetMaxHealth();

	Hp = FMath::Clamp(Hp - Damage, 0, MaxHp);
	AttributeSet->SetHealth(Hp);

	if (Hp == 0)
	{
		OnDead(Attacker);
	}

	//D(FString::Printf(TEXT("%d"), Hp));
}

void AG1Character::OnDead(TObjectPtr<AG1Character> Attacker)
{
	if (State == ECharacterState::Dead)
	{
		return;
	}

	State = ECharacterState::Dead;
}

void AG1Character::InitEquipment()
{
	if (const UG1ItemData* ItemData = UG1AssetManager::GetAssetByName<UG1ItemData>("Item_Weapon"))
	{
		for (const FName ID : EquipmentList)
		{
			const FG1ItemInfo* ItemInfo = ItemData->FindItemInfo(ID);
			if (ItemInfo == nullptr)
				continue;

			if (ItemInfo->EquipmentStaticMesh != nullptr)
			{
				AG1EquipmentItem* EquipItem = GetWorld()->SpawnActor<AG1EquipmentItem>(ItemInfo->EquipmentStaticMesh);
				EquipItem->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, TEXT("hand_r"));
				EquipItem->SetOwner(this);
				EquipObjectList.Add(ID, EquipItem);
			}

			AbilitySystem->AddEquipmentGameplayEffect(ID);
		}
	}

	
}

void AG1Character::AddEquipment(const FName EquipID)
{
}

void AG1Character::RemoveEquipment(const FName EquipID)
{
}

void AG1Character::InitAbilitySystem()
{
	
}

void AG1Character::Highlight()
{
	bHighlighted = true;
	GetMesh()->SetRenderCustomDepth(true);
	GetMesh()->SetCustomDepthStencilValue(250);
}
void AG1Character::UnHighlight()
{
	bHighlighted = false;
	GetMesh()->SetRenderCustomDepth(false);
}

void AG1Character::AddCharacterAbilities()
{
	UG1AbilitySystem* AS = Cast<UG1AbilitySystem>(AbilitySystem);
	if (AS == nullptr)
	{
		return;
	}

	AS->AddCharacterAbilities(StartupAbilities);
}

void AG1Character::ActivateAbility(FGameplayTag AbilityTag)
{
	if (AbilitySystem)
		AbilitySystem->ActivateAbility(AbilityTag);
}

bool AG1Character::IsAttackState()
{
	return State == ECharacterState::MoveAttack;
}

bool AG1Character::IsSameTeam(const AActor* Ohter) const
{
	const AG1Character* OtherCharacter = Cast<AG1Character>(Ohter);

	if (!OtherCharacter)
	{
		return false;
	}

	return TeamTag == OtherCharacter->TeamTag;
}

bool AG1Character::IsEnemyTeam(const AActor* Ohter) const
{
	const AG1Character* OtherCharacter = Cast<AG1Character>(Ohter);

	if (!OtherCharacter)
	{
		return false;
	}

	return TeamTag != OtherCharacter->TeamTag;
}

float AG1Character::TotalDemage() const
{
	return AttributeSet->GetBaseDamage();
}

bool AG1Character::IsDeadG1Character() const
{
	return State == ECharacterState::Dead;
}

