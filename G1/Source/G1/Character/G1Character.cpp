// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/G1Character.h"

#include "GameplayEffectExtension.h"

#include "AbilitySystem/G1AbilitySystem.h"
#include "AbilitySystem/Attributes/G1AttributeSet.h"
#include "G1CharacterDefine.h"
#include "System/G1AssetManager.h"
#include "Data/G1ItemData.h"
#include "Item/G1EquipmentItem.h"

#include "Components/SceneComponent.h"
#include "Components/WidgetComponent.h"

#include "Engine/EngineTypes.h"
#include "Utility/G1GameplayTags.h"
#include "G1CharacterConditionData.h"
#include "Animation/G1AnimInstance.h"
#include "Animation/AnimMontage.h"
#include "Components/SkeletalMeshComponent.h"
#include "Item/G1DropItem.h"
#include "Data/G1DropTableData.h"

#include "UI/G1HpBarWidget.h"

// Sets default values
AG1Character::AG1Character()
	: Super()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TeamTag = G1GameplayTags::Team_None;

	MonsterDropID = NAME_None;

	HpBarComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("HealthBar"));
	HpBarComponent->SetupAttachment(GetRootComponent());
}

// Called when the game starts or when spawned
void AG1Character::BeginPlay()
{
	Super::BeginPlay();
	
	if (AbilitySystem)
	{
		AbilitySystem->GetGameplayAttributeValueChangeDelegate(
			UG1AttributeSet::GetBaseDamageAttribute()
		).AddUObject(this, &AG1Character::Delegate_OnBaseDamageChanged);
	}

	if (HpBarClass->IsValidLowLevel())
	{
		HpBarComponent->SetWidgetClass(HpBarClass);
		HpBarComponent->SetWidgetSpace(EWidgetSpace::Screen);
		HpBarComponent->SetDrawAtDesiredSize(true);
		HpBarComponent->SetRelativeLocation(FVector(0, 0, 100));
	}

	UpdateHp();

	if (USkeletalMeshComponent* MeshComp = GetMesh())
	{
		if (UAnimInstance* RawAnim = MeshComp->GetAnimInstance())
		{
			AnimInstance = Cast<UG1AnimInstance>(RawAnim);
		}
	}

	//AddCharacterAbilities();

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
			if (InDeadState())
			{
				return;
			}

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

		else if (IsValid(AnimInstance) && Montage == AnimInstance->GetDeathAnimMontage())
		{
			if (USkeletalMeshComponent* MeshComp = GetMesh())
			{
				MeshComp->bPauseAnims = true;
				MeshComp->SetComponentTickEnabled(false);
			}
			AnimInstance->EnableAnimInstance = false;
			SetActorTickEnabled(false);
			AnimInstance->StopAllMontages(0.0f);
			AnimInstance->SetRootMotionMode(ERootMotionMode::IgnoreRootMotion);
		}
	}

	else if (EventTag == G1GameplayTags::Event_Montage_Attack_Start
				|| EventTag == G1GameplayTags::Event_Montage_Attack_End)
	{
		if (InDeadState())
		{
			return;
		}

		for (const TPair<EEquipmentType, TObjectPtr<AG1EquipmentItem>>& Pair : EquipObjectList)
		{
			EEquipmentType Type = Pair.Key;
			TObjectPtr<AG1EquipmentItem> Item = Pair.Value;

			if (Type != EEquipmentType::Weapon)
			{
				continue;
			}

			if (IsValid(Item.Get()))
			{
				Item->SetWeaponCollisionEnabled(EventType == ECharacterAnimNotiType::OnQueryOnly);
			}
		}
	}
}

void AG1Character::HandleEventAnimNotifyStateBegin(UAnimMontage* Montage, FGameplayTag EventTag)
{
	if (InDeadState())
	{
		return;
	}

	if (EventTag == G1GameplayTags::Event_AnimNotiState_Montage)
	{
		SetSatate(ECharacterState::Ability);
	}
	else if (EventTag == G1GameplayTags::Event_AnimNotiState_Attack)
	{
		SetWeaponCollisionEnabled(true);
	}
}

void AG1Character::HandleEventAnimNotifyStateEnd(UAnimMontage* Montage, FGameplayTag EventTag)
{
	if (InDeadState())
	{
		return;
	}

	if (EventTag == G1GameplayTags::Event_AnimNotiState_Montage)
	{
		if (State == ECharacterState::Ability)
		{
			SetSatate(ECharacterState::Idle);
		}
	}
	else if (EventTag == G1GameplayTags::Event_AnimNotiState_Attack)
	{
		SetWeaponCollisionEnabled(false);
	}
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
	if (!IsValid(AttributeSet))
	{
		UE_LOG(LogTemp, Warning, TEXT("%s OnDamaged: AttributeSet is null"), *GetName());
		return;
	}

	float Hp = AttributeSet->GetHealth();
	float MaxHp = AttributeSet->GetMaxHealth();

	Hp = FMath::Clamp(Hp - Damage, 0, MaxHp);
	AttributeSet->SetHealth(Hp);

	UpdateHp();

	if (Hp == 0)
	{
		OnDead(Attacker);

		if (IsValid(AnimInstance))
		{
			G1PlayAnimMontage(AnimInstance->GetDeathAnimMontage());
		}
	}
	else
	{
		AddConditionData(EConditionType::Hit, 0.5f, 1.f);

		if (IsValid(AnimInstance))
		{
			FVector Forward = GetActorForwardVector();
			FVector Right = GetActorRightVector();

			if (!IsValid(Attacker.Get()))
			{
				// 공격자 정보가 없으면 기본 전방 히트로 처리
				return;
			}

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
	if (USkeletalMeshComponent* MeshComp = GetMesh())
	{
		MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}

	/// 죽을때 아이템 드랍
	CreateDropItem(Attacker);

	OnCharacterDead.Broadcast(this);

	// 일정 시간 후 삭제
	SetLifeSpan(5.0f);

	/// 장착한 아이템도 삭제
	for (const TPair<EEquipmentType, TObjectPtr<AG1EquipmentItem>>& Pair : EquipObjectList)
	{
		TObjectPtr<AG1EquipmentItem> Item = Pair.Value;

		if (IsValid(Item.Get()))
		{
			Item->SetLifeSpan(5.f);
		}
	}
}

void AG1Character::InitEquipment()
{
	auto WeaponItemData = UG1AssetManager::GetAssetByName<UG1ItemData>("Item_Weapon");
	if (WeaponItemData == nullptr)
	{
		UE_LOG(LogTemp, Log, TEXT("InitEquipment Error, Item_Weapon Asset Load Fail"));
		return;
	}

	for (const TPair<EEquipmentType, FName>& Pair : EquipmentMap)
	{
		EEquipmentType Type = Pair.Key;
		FName ItemID = Pair.Value;

		AddEquipment(ItemID);
	}
}

bool AG1Character::AddEquipment(const FName EquipID)
{
	if (AbilitySystem == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("InitEquipment: UG1AbilitySystem is null"));
		return false;
	}

	auto WeaponItemData = UG1AssetManager::GetAssetByName<UG1ItemData>("Item_Weapon");

	const FG1ItemInfo* ItemInfo = WeaponItemData->FindItemInfo(EquipID);
	if (ItemInfo == nullptr)
	{
		return false;
	}

	if (ItemInfo->EquipmentStaticMesh != nullptr)
	{
		UWorld* World = GetWorld();
		if (!IsValid(World))
		{
			UE_LOG(LogTemp, Warning, TEXT("InitEquipment: World is null"));
			return false;
		}

		AG1EquipmentItem* EquipItem = World->SpawnActor<AG1EquipmentItem>(ItemInfo->EquipmentStaticMesh);
		if (IsValid(EquipItem) && IsValid(GetMesh()))
		{
			if (ItemInfo->EquipType == EEquipmentType::Weapon)
			{
				EquipItem->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, TEXT("hand_r"));
			}
			else
			{
				EquipItem->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, TEXT("shield_Socket"));
			}

			EquipItem->EquipItemSetOwner(this);
			EquipItem->InitEquipment(EquipID);

			if (EquipObjectList.Contains(ItemInfo->EquipType))
			{
				EquipObjectList[ItemInfo->EquipType] = EquipItem;
			}
			else
			{
				EquipObjectList.Add(ItemInfo->EquipType, EquipItem);
			}
			
			AbilitySystem->AddItemAbilities(EquipItem->ItemAbilities);
			AbilitySystem->AddEquipmentGameplayEffect(EquipID);

			OnAddEquipment.Broadcast(this, EquipID);
		}
	}

	return true;
}

void AG1Character::RemoveEquipment(const EEquipmentType EquipType)
{
	TObjectPtr<AG1EquipmentItem> EquipItem = EquipObjectList[EquipType];
	if (EquipItem == nullptr)
	{
		return;
	}

	if (AbilitySystem == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s RemoveEquipment: UG1AbilitySystem is null"), *GetName());
		return;
	}

	AbilitySystem->RemoveEquipmentGameplayEffect(EquipItem->ItemID);
	AbilitySystem->RemoveItemAbilities(EquipItem->ItemAbilities);
	EquipItem->Destroy();
	EquipObjectList[EquipType] = nullptr;

	OnRemoveEquipment.Broadcast(this, EquipType);
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
	if (USkeletalMeshComponent* MeshComp = GetMesh())
	{
		MeshComp->SetRenderCustomDepth(true);
		MeshComp->SetCustomDepthStencilValue(250);
	}
}
void AG1Character::UnHighlight()
{
	bHighlighted = false;
	if (USkeletalMeshComponent* MeshComp = GetMesh())
	{
		MeshComp->SetRenderCustomDepth(false);
	}
}

void AG1Character::Delegate_OnBaseDamageChanged(const FOnAttributeChangeData& Data)
{
	UE_LOG(LogTemp, Warning, TEXT("===== BaseDamage Changed ====="));
	UE_LOG(LogTemp, Warning, TEXT("Old: %f New: %f Delta: %f"),
		Data.OldValue,
		Data.NewValue,
		Data.NewValue - Data.OldValue);

	if (Data.GEModData)
	{
		const UGameplayEffect* GE = Data.GEModData->EffectSpec.Def;
		if (GE)
		{
			UE_LOG(LogTemp, Warning, TEXT("Effect: %s"), *GE->GetName());
		}
	}
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
	if (IsValid(AbilitySystem))
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
	if (IsValid(AttributeSet))
	{
		return AttributeSet->GetBaseDamage();
	}
	return 0.0f;
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

void AG1Character::UpdateHp()
{
	if (AttributeSet == nullptr)
	{
		return;
	}

	float Hp = AttributeSet->GetHealth();
	float MaxHp = AttributeSet->GetMaxHealth();

	if (HpBarComponent)
	{
		if (Hp <= 0)
		{
			HpBarComponent->SetHiddenInGame(true);
		}
		else
		{
			UG1HpBarWidget* HpBar = Cast<UG1HpBarWidget>(HpBarComponent->GetUserWidgetObject());
			if (HpBar)
			{
				float Ratio = static_cast<float>(Hp) / MaxHp;
				HpBar->SetHpRatio(Ratio);
			}
		}
	}
}

void AG1Character::SetWeaponCollisionEnabled(bool Enabled)
{
	for (const TPair<EEquipmentType, TObjectPtr<AG1EquipmentItem>>& Pair : EquipObjectList)
	{
		EEquipmentType Type = Pair.Key;
		TObjectPtr<AG1EquipmentItem> Item = Pair.Value;

		if (Type != EEquipmentType::Weapon)
		{
			continue;
		}

		if (IsValid(Item.Get()))
		{
			Item->SetWeaponCollisionEnabled(Enabled);
		}
	}
}

void AG1Character::G1PlayAnimMontage(UAnimMontage* Montage)
{
	if (IsValid(AnimInstance) && Montage != nullptr)
	{
		AnimInstance->Montage_Play(Montage);
	}
}

void AG1Character::CreateDropItem(TObjectPtr<AG1Character> DropItemOwner)
{
	if (MonsterDropID == NAME_None)
	{
		return;
	}

	const UG1DropTableData* DropData = UG1AssetManager::GetAssetByName<UG1DropTableData>("MonsterDropData");
	if (DropData == nullptr)
	{
		return;
	}

	const UG1ItemData* ItemData = UG1AssetManager::GetAssetByName<UG1ItemData>("Item_Weapon");
	if (ItemData == nullptr)
	{
		return;
	}

	TArray<FG1DropResult> Drops;
	DropData->RollDrops(MonsterDropID, Drops);
	for (const FG1DropResult& R : Drops)
	{
		const FG1ItemInfo* Info = ItemData->FindItemInfo(R.ItemID);
		if (Info == nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("%s CreateDropItem: No item info found for ItemID %s"), *GetName(), *R.ItemID.ToString());
			continue;
		}
		if (IsValid(Info->DropStaticMeshClass) == false)
		{
			UE_LOG(LogTemp, Warning, TEXT("%s CreateDropItem: Item %s will drop %d"), *GetName(), *R.ItemID.ToString(), R.Count);
			continue;
		}

		UWorld* World = GetWorld();
		if (World == nullptr)
		{
			continue;
		}

		FVector SpawnLoc = GetActorLocation(); // + 오프셋
		FRotator SpawnRot = FRotator::ZeroRotator;

		// 우선 DropActorClass 우선 사용
		AG1DropItem* DropItem = World->SpawnActor<AG1DropItem>(Info->DropStaticMeshClass);
		if (IsValid(DropItem) && IsValid(GetMesh()))
		{
			DropItem->SetActorLocation(SpawnLoc);
			DropItem->SetActorRotation(SpawnRot);
			DropItem->SetDropItem(R.ItemID);
		}
	}
}
