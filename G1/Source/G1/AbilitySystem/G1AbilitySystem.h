// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "GameplayTagContainer.h"
#include "Abilities/GameplayAbility.h"
#include "G1AbilitySystem.generated.h"

class UG1ItemData;

/**
 * 
 */
UCLASS()
class G1_API UG1AbilitySystem : public UAbilitySystemComponent
{
	GENERATED_BODY()
	
public:
	void AddCharacterAbilities(const TArray<TSubclassOf<class UGameplayAbility>>& StartupAbilities);
	void AddItemAbilities(const TArray<TSubclassOf<class UGameplayAbility>>& ItemAbilities);
	void RemoveItemAbilities(const TArray<TSubclassOf<class UGameplayAbility>>& ItemAbilities);

	void AddEquipmentGameplayEffect(const FName EquipID);
	void RemoveEquipmentGameplayEffect(const FName EquipID);

	void ActivateAbility(FGameplayTag AbilityTag);

	TArray<FGameplayAbilitySpecHandle> SpecHandles;

	TMap<FName, FActiveGameplayEffectHandle> EquipHandles;

private:
	void LogActiveGameplayEffects();
};
