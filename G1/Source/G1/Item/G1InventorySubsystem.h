// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"


#include "G1InventorySubsystem.generated.h"

class UG1Item2DInstance;
/**
 * 
 */
UCLASS()
class G1_API UG1InventorySubsystem : public UWorldSubsystem
{
	GENERATED_BODY()
	
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	virtual void Deinitialize() override;

	void AddDefaultItems();

	const TArray<TObjectPtr<UG1Item2DInstance>>& GetItems() { return Items; }

protected:
	TArray<TObjectPtr<UG1Item2DInstance>> Items;
};
