// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/G1PlayerState.h"
#include "AbilitySystem/G1AbilitySystem.h"
#include "AbilitySystem/Attributes/G1PlayerSet.h"

AG1PlayerState::AG1PlayerState(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	AbilitySystem = CreateDefaultSubobject<UG1AbilitySystem>("AbilitySystem");
	PlayerSet = CreateDefaultSubobject<UG1PlayerSet>("PlayerSet");
}

UAbilitySystemComponent* AG1PlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystem;
}

UG1AbilitySystem* AG1PlayerState::GetG1AbilitySystemComponent() const
{
	return AbilitySystem;
}

UG1PlayerSet* AG1PlayerState::GetG1PlayerSet() const
{
	return PlayerSet;
}
