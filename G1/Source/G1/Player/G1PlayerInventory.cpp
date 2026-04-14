// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/G1PlayerInventory.h"
#include "System/G1AssetManager.h"
#include "Data/G1ItemData.h"
#include "Item/G1Item2DInstance.h"

#include "Subsystems/SubsystemBlueprintLibrary.h"
#include "Item/G1InventorySubsystem.h"

UG1InventoryComponent::UG1InventoryComponent()
	: Super()
{
	InventorySize.X = 10;
	InventorySize.Y = 5;
}

void UG1InventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	ItemData = UG1AssetManager::GetAssetByName<UG1ItemData>("Item_Weapon");

	UG1InventorySubsystem* Inventory = Cast<UG1InventorySubsystem>(USubsystemBlueprintLibrary::GetWorldSubsystem(this, UG1InventorySubsystem::StaticClass()));
	if (Inventory == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("UG1InventoryComponent::BeginPlay: InventorySubsystem is null"));
		return;
	}

	InventorySize = Inventory->GetInventorySize();
	InventoryItems.SetNum(InventorySize.X * InventorySize.Y);

	const TArray<FG1InventoryItemData>& ItemDatas = Inventory->GetItemDatas();
	for (int i = 0; i < ItemDatas.Num(); i++)
	{
		if (ItemDatas[i].ItemID.IsNone())
		{
			continue;
		}

		InventoryItems[i] = NewObject<UG1Item2DInstance>(this);
		InventoryItems[i]->Init(i % InventorySize.X, i / InventorySize.X, ItemDatas[i].ItemID, ItemDatas[i].Count, ItemData);
	}
}

bool UG1InventoryComponent::PickUpItem(const FName ItemID, const int32 Count)
{
	/// 중첩이 아닌경우 추가될 위치 저장
	int X = 0; int Y = 0;
	bool bFoundStackable = false;

	for (int i = 0; i < InventoryItems.Num(); i ++)
	{
		if (InventoryItems[i]->bIsStackable && InventoryItems[i]->ItemID.IsEqual(ItemID))
		{
			InventoryItems[i]->Count += Count;
			return true;
		}

		else if (bFoundStackable == false && InventoryItems[i] == nullptr)
		{
			X = i % InventorySize.X;
			Y = i / InventorySize.X;
			bFoundStackable = true;
		}
	}

	if (bFoundStackable)
	{
		AddItem(X, Y, ItemID, Count);
		return true;
	}
	else
	{
		return false;
	}
}

void UG1InventoryComponent::AddItem(const int32 X, const int32 Y, const FName ItemID, const int32 Count)
{
	if (ItemData == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("UG1InventoryComponent::AddItem: ItemData is null"));
		return;
	}

	int32 Index = GetIndex(X, Y);

	if (InventoryItems[Index] == nullptr)
	{
		InventoryItems[Index] = NewObject<UG1Item2DInstance>(this);
		InventoryItems[Index]->Init(X, Y, ItemID, Count, ItemData);
	}
	else if (InventoryItems[Index]->ItemID.IsEqual(ItemID) && InventoryItems[Index]->bIsStackable)
	{
		InventoryItems[Index]->Count += Count;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("UG1InventoryComponent::AddItem: Slot (%d, %d) is occupied by a different item"), X, Y);
	}
}

void UG1InventoryComponent::RemoveItem(const FName ItemID, const int32 Count)
{
	if (ItemData == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("UG1InventoryComponent::RemoveItem: ItemData is null"));
		return;
	}

	for (int i = 0; i < InventoryItems.Num(); i++)
	{
		if (InventoryItems[i]->ItemID.IsEqual(ItemID))
		{
			if (InventoryItems[i]->Count > Count)
			{
				InventoryItems[i]->Count -= Count;
			}
			else
			{
				InventoryItems[i] = nullptr;
			}
			break;
		}
	}
}

void UG1InventoryComponent::RemoveItem(const int32 X, const int32 Y, const int32 Count)
{
	if (ItemData == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("UG1InventoryComponent::RemoveItem: ItemData is null"));
		return;
	}

	int32 Index = GetIndex(X, Y);

	if (InventoryItems[Index]->Count > Count)
	{
		InventoryItems[Index]->Count -= Count;
	}
	else
	{
		InventoryItems[Index] = nullptr;
	}
}

int32 UG1InventoryComponent::GetIndex(const int32 X, const int32 Y)
{
	return (Y * InventorySize.X) + X;
}

TObjectPtr<UG1Item2DInstance> UG1InventoryComponent::GetItem(const int32 X, const int32 Y)
{
	int32 Index = GetIndex(X, Y);
	return InventoryItems[Index];
}

TArray<TObjectPtr<UG1Item2DInstance>> UG1InventoryComponent::GetInventoryItems() const
{
	return InventoryItems;
}

const FIntPoint& UG1InventoryComponent::GetInventorySize() const
{
	return InventorySize;
}
