// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/G1AbilitySystem.h"
#include "System/G1AssetManager.h"
#include "Data/G1ItemData.h"

void UG1AbilitySystem::AddCharacterAbilities(const TArray<TSubclassOf<class UGameplayAbility>>& StartupAbilities)
{
	for (auto& AbilityClass : StartupAbilities)
	{
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(AbilityClass, 1);

		FGameplayAbilitySpecHandle SpecHandle = GiveAbility(AbilitySpec);

		// GiveAbility 로 보여한 스킬로 활성화된 어빌리티에 대한 정보??
		//auto& a = ActivatableAbilities;

		//GiveAbilityAndActivateOnce(AbilitySpec);

		SpecHandles.Add(SpecHandle);
	}
}

void UG1AbilitySystem::AddItemAbilities(const TArray<TSubclassOf<class UGameplayAbility>>& ItemAbilities)
{
	for (auto& AbilityClass : ItemAbilities)
	{
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(AbilityClass, 1);

		FGameplayAbilitySpecHandle SpecHandle = GiveAbility(AbilitySpec);

		SpecHandles.Add(SpecHandle);
	}
}

void UG1AbilitySystem::RemoveItemAbilities(const TArray<TSubclassOf<class UGameplayAbility>>& ItemAbilities)
{
	for (auto& AbilityClass : ItemAbilities)
	{
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(AbilityClass, 1);

		FGameplayAbilitySpecHandle SpecHandle = GiveAbility(AbilitySpec);

		if (SpecHandles.Contains(SpecHandle))
			SpecHandles.Remove(SpecHandle);
	}
}

void UG1AbilitySystem::AddEquipmentGameplayEffect(const FName EquipID)
{
	auto ItemData = UG1AssetManager::GetAssetByName<UG1ItemData>("Item_Weapon");

	const FG1ItemInfo* ItemInfo = ItemData->FindItemInfo(EquipID);
	if (ItemInfo != nullptr && ItemInfo->ItemEffect != nullptr)
	{
		FGameplayEffectContextHandle Context = MakeEffectContext();
		FGameplayEffectSpecHandle SpecHandle = MakeOutgoingSpec(ItemInfo->ItemEffect, 1.f, Context);

		if (SpecHandle.IsValid())
		{
			EquipHandles.Add(EquipID, ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get()));
		}
	}
}

void UG1AbilitySystem::RemoveEquipmentGameplayEffect(const FName EquipID)
{
	if (EquipHandles.Contains(EquipID))
	{
		RemoveActiveGameplayEffect(EquipHandles[EquipID]);
		EquipHandles.Remove(EquipID);
	}
}

void UG1AbilitySystem::ActivateAbility(FGameplayTag AbilityTag)
{
	for (FGameplayAbilitySpecHandle& SpecHandle : SpecHandles)
	{
		TryActivateAbility(SpecHandle);
	}
}
