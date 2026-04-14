// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/G1InventorySubsystem.h"
#include "G1Item2DInstance.h"

void UG1InventorySubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	InventorySize.X = 10;
	InventorySize.Y = 5;

	ItemDatas.SetNum(InventorySize.X * InventorySize.Y);
	for (auto& Item : ItemDatas)
	{
		Item.ItemID = NAME_None;
		Item.Count = 0;
		Item.IsStackable = false;
	}
}

void UG1InventorySubsystem::Deinitialize()
{
	Super::Deinitialize();
}