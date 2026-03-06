// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/G1AbilitySystem.h"

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

void UG1AbilitySystem::ActivateAbility(FGameplayTag AbilityTag)
{
	for (FGameplayAbilitySpecHandle& SpecHandle : SpecHandles)
	{
		TryActivateAbility(SpecHandle);
	}
}
