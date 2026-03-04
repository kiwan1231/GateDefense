// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GamePlayTagContainer.h"
#include "Engine/DataAsset.h"
#include "G1PlayerInputData.generated.h"

class UInputAction;
class UInputMappingContext;

USTRUCT()
struct FG1InputAction
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly)
	FGameplayTag InputTag = FGameplayTag::EmptyTag;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UInputAction> InputAction = nullptr;
};

/**
 * 
 */
UCLASS()
class G1_API UG1PlayerInputData : public UDataAsset
{
	GENERATED_BODY()
	
public:
	const UInputAction* FindInputActionByTag(const FGameplayTag& InputTag) const;

public:
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UInputMappingContext> InputMappingContext;

	UPROPERTY(EditDefaultsOnly)
	TArray<FG1InputAction> InputActions;
};
