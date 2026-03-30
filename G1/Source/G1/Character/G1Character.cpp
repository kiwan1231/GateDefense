// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/G1Character.h"
#include "AbilitySystem/G1AbilitySystem.h"
#include "AbilitySystem/Attributes/G1AttributeSet.h"
#include "G1CharacterDefine.h"
#include "System/G1AssetManager.h"
#include "Data/G1ItemData.h"
#include "Item/G1EquipmentItem.h"
#include "Components/SceneComponent.h"
#include "Engine/EngineTypes.h"
#include "Utility/G1GameplayTags.h"
#include "G1CharacterConditionData.h"
#include "Animation/G1AnimInstance.h"
#include "Animation/AnimMontage.h"

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
	
	AnimInstance = Cast<UG1AnimInstance>(GetMesh()->GetAnimInstance());
	
	AddCharacterAbilities();

	InitEquipment();
}

// Called every frame
void AG1Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UpdateConditionData(DeltaTime);
	CheckConditionEffect();
}

void AG1Character::HandleGameplayEvent(UAnimMontage* Montage, FGameplayTag EventTag, ECharacterAnimNotiType EventType)
{
	if (EventTag == G1GameplayTags::Event_Montage_Begin)
	{
		if (EventType == ECharacterAnimNotiType::InAbilityState)
		{
			SetSatate(ECharacterState::Ability);
		}
	}

	else if (EventTag == G1GameplayTags::Event_Montage_End)
	{
		if (EventType == ECharacterAnimNotiType::OutAbilityState)
		{
			if (State == ECharacterState::Ability)
			{
				SetSatate(ECharacterState::Idle);
			}
		}

		else if (Montage == AnimInstance->GetDeathAnimMontage())
		{
			GetMesh()->bPauseAnims = true;
			GetMesh()->SetComponentTickEnabled(false);
			AnimInstance->EnableAnimInstance = false;
			SetActorTickEnabled(false);
			AnimInstance->StopAllMontages(0.0f);
			AnimInstance->SetRootMotionMode(ERootMotionMode::IgnoreRootMotion);
		}
	}

	else if (EventTag == G1GameplayTags::Event_Montage_Attack_Start
				|| EventTag == G1GameplayTags::Event_Montage_Attack_End)
	{
		for (const TPair<FName, TObjectPtr<AG1EquipmentItem>>& Pair : EquipObjectList)
		{
			FName Key = Pair.Key;
			TObjectPtr<AG1EquipmentItem> Item = Pair.Value;

			if (Item != nullptr)
			{
				Item->SetWeaponCollisionEnabled(EventType == ECharacterAnimNotiType::OnQueryOnly);
			}
		}
	}
	

	/*if (EventType == ECharacterAnimNotiType::OnQueryOnly)
	{
		RHandHitBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	}
	else if (EventType == ECharacterAnimNotiType::NoCollision)
	{
		RHandHitBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}*/
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

void AG1Character::OnDamaged(int32 Damage, TObjectPtr<AG1Character> Attacker, const FHitResult& SweepResult)
{
	float Hp = AttributeSet->GetHealth();
	float MaxHp = AttributeSet->GetMaxHealth();

	Hp = FMath::Clamp(Hp - Damage, 0, MaxHp);
	AttributeSet->SetHealth(Hp);

	if (Hp == 0)
	{
		OnDead(Attacker);

		if (AnimInstance != nullptr)
		{
			G1PlayAnimMontage(AnimInstance->GetDeathAnimMontage());
		}
	}
	else
	{
		AddConditionData(EConditionType::Hit, 0.5f, 1.f);

		if (AnimInstance != nullptr)
		{
			FVector Forward = GetActorForwardVector();
			FVector Right = GetActorRightVector();

			FVector HitDir = Attacker->GetActorLocation() - GetActorLocation();
			HitDir.Z = 0.f; // 수평만 판단
			HitDir.Normalize();

			// 전후 판단 (내적)
			float ForwardDot = FVector::DotProduct(Forward, HitDir);

			// 좌우 판단 (내적)
			float RightDot = FVector::DotProduct(Right, HitDir);

			FName SectionName = (FMath::Abs(ForwardDot) >= FMath::Abs(RightDot))
								? (ForwardDot >= 0.f) ? "Hit_Front" : "Hit_Back"
								: (RightDot >= -0.f) ? "Hit_Right" : "Hit_Left";


			auto HitMontage = AnimInstance->GetHitAnimMontage();
			G1PlayAnimMontage(HitMontage);
			AnimInstance->Montage_JumpToSection(SectionName, HitMontage);
		}
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

	// 충돌 비활성화 (선택)
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	OnCharacterDead.Broadcast(this);

	// 일정 시간 후 삭제
	SetLifeSpan(5.0f);

	for (const TPair<FName, TObjectPtr<AG1EquipmentItem>>& Pair : EquipObjectList)
	{
		FName Key = Pair.Key;
		TObjectPtr<AG1EquipmentItem> Item = Pair.Value;

		if (Item != nullptr)
		{
			Item->SetLifeSpan(5.f);
		}
	}
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

void AG1Character::UpdateConditionData(float DeltaTime)
{
	for (int32 i = ConditionDataList.Num() - 1; i >= 0; --i)
	{
		FG1CharacterConditionData& Data = ConditionDataList[i];

		if (Data.DurationTime == -1)
			continue;

		Data.DurationTime = FMath::Max(0.0f, Data.DurationTime - DeltaTime);

		if (Data.DurationTime == 0)
		{
			ConditionDataList.RemoveAt(i);
		}
	}

	//ConditionDataList.RemoveAll([DeltaTime](FG1ConditionData& Data)
	//	{
	//		if (Data.DurationTime == -1)
	//			return false;
	//
	//		Data.DurationTime = FMath::Clamp(Data.DurationTime - DeltaTime, 0.0f, Data.DurationTime);
	//
	//		return Data.DurationTime == 0;
	//	});*/
}

void AG1Character::AddConditionData(EConditionType Type, float DurationTime, float Value1)
{
	if (Type == EConditionType::Hit)
	{
		FG1CharacterConditionData* HitData = ConditionDataList.FindByPredicate(
			[Type](const FG1CharacterConditionData& Data)
			{
				return Data.Type == Type;
			}
		);

		int DivideValue = 1;
		if (HitData != nullptr)
		{
			HitData->int1 = HitData->int1 + 1;
			HitData->DurationTime = DurationTime / HitData->int1;
		}
		else
		{
			FG1CharacterConditionData Data;
			Data.Type = EConditionType::Hit;
			Data.DurationTime = DurationTime;
			Data.int1 = 1;
			ConditionDataList.Add(Data);
		}

		State = ECharacterState::ConditionEffect;
	}
}

void AG1Character::CheckConditionEffect()
{
	if (State == ECharacterState::Dead)
	{
		return;
	}

	for (int32 i = 0; i < ConditionDataList.Num(); i++)
	{
		auto Type = ConditionDataList[i].Type;
		if (Type == EConditionType::Hit || Type == EConditionType::Stun)
		{
			State = ECharacterState::ConditionEffect;
			return;
		}
	}

	if (State == ECharacterState::ConditionEffect)
	{
		State = ECharacterState::Idle;
	}
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

void AG1Character::SetSatate(ECharacterState _State)
{
	State = _State;
}

bool AG1Character::InAttackState() const
{
	return State == ECharacterState::Attack;
}

bool AG1Character::InAbilityState() const
{
	return State == ECharacterState::Ability;
}

bool AG1Character::InDeadState() const
{
	return State == ECharacterState::Dead;
}

bool AG1Character::InConditionEffectState() const
{
	return State == ECharacterState::ConditionEffect;
}

bool AG1Character::EnableMove() const
{
	if (InAttackState() || 
		InAbilityState() ||
		InConditionEffectState() ||
		InDeadState())
	{
		return false;
	}

	return true;
}

bool AG1Character::EnableJump() const
{
	if (InAttackState() || 
		InAbilityState() ||
		InConditionEffectState() ||
		InDeadState())
	{
		return false;
	}

	return true;
}

bool AG1Character::EnableAttack() const
{
	if (InAttackState() ||
		InAbilityState() ||
		InConditionEffectState() ||
		InDeadState())
	{
		return false;
	}

	return true;
}

bool AG1Character::EnableAbility() const
{
	if (InAttackState() ||
		InAbilityState() ||
		InConditionEffectState() ||
		InDeadState())
	{
		return false;
	}

	return true;
}

void AG1Character::G1PlayAnimMontage(UAnimMontage* Montage)
{
	if (AnimInstance != nullptr && Montage != nullptr)
	{
		AnimInstance->Montage_Play(Montage);
	}
}
