// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "AbilitySystemInterface.h"

#include "G1PlayerState.generated.h"

/**
 * 
 */
UCLASS()
class G1_API AG1PlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()
	
public:
	AG1PlayerState(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

public:
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const;

	class UG1AbilitySystem* GetG1AbilitySystemComponent() const;
	class UG1PlayerSet* GetG1PlayerSet() const;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UG1AbilitySystem> AbilitySystem;

	UPROPERTY()
	TObjectPtr<UG1PlayerSet> PlayerSet;
};
