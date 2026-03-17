// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/G1InventorySubsystem.h"
#include "G1Item2DInstance.h"

void UG1InventorySubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void UG1InventorySubsystem::Deinitialize()
{
	Super::Deinitialize();
}

void UG1InventorySubsystem::AddDefaultItems()
{
	TObjectPtr<UG1Item2DInstance> Item = NewObject<UG1Item2DInstance>();
	Item->Init(100);
	Items.Add(Item);
}
