// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/G1PlayerInventory.h"
#include "System/G1AssetManager.h"
#include "Data/G1ItemData.h"

UG1InventoryComponent::UG1InventoryComponent()
	: Super()
{

}

void UG1InventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	ItemData = UG1AssetManager::GetAssetByName<UG1ItemData>("Item_Weapon");

	Items.SetNum(SizeX * SizeY);
	for (auto& Item : Items)
	{
		Item.ItemID = NAME_None;
		Item.Count = 0;
		Item.IsStackable = false;
	}
}

bool UG1InventoryComponent::PickUpItem(const FName ItemID, const int32 Count)
{
	/// 중첩이 아닌경우 추가될 위치 저장
	int X = 0; int Y = 0;
	bool bFoundStackable = false;

	for (int i = 0; i <Items.Num(); i ++)
	{
		if (Items[i].IsStackable && Items[i].ItemID.IsEqual(ItemID))
		{
			Items[i].Count += Count;
			return true;
		}

		else if (bFoundStackable == false && Items[i].ItemID.IsNone())
		{
			X = i % SizeX;
			Y = i / SizeX;
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

	if (Items[Index].ItemID.IsNone())
	{
		Items[Index].ItemID = ItemID;
		Items[Index].Count = Count;
		const FG1ItemInfo* ItemInfo = ItemData->FindItemInfo(ItemID);
		Items[Index].IsStackable = ItemInfo ? ItemInfo->Stackable : false;
	}
	else if (Items[Index].ItemID.IsEqual(ItemID) && Items[Index].IsStackable)
	{
		Items[Index].Count += Count;
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

	for (int i = 0; i < Items.Num(); i++)
	{
		if (Items[i].ItemID.IsEqual(ItemID))
		{
			if (Items[i].Count > Count)
			{
				Items[i].Count -= Count;
			}
			else
			{
				Items[i].ItemID = NAME_None;
				Items[i].IsStackable = false;
				Items[i].Count = 0;
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

	if (Items[Index].Count > Count)
	{
		Items[Index].Count -= Count;
	}
	else
	{
		Items[Index].ItemID = NAME_None;
		Items[Index].IsStackable = false;
		Items[Index].Count = 0;
	}
}

int32 UG1InventoryComponent::GetIndex(const int32 X, const int32 Y)
{
	return Y * SizeX + X;
}

FG1InventoryItemData* UG1InventoryComponent::GetItem(const int32 X, const int32 Y)
{
	int32 Index = GetIndex(X, Y);
	return Items.IsValidIndex(Index) ? &Items[Index] : nullptr;
}

TArray<FG1InventoryItemData> UG1InventoryComponent::GetItems() const
{
	return Items;
}
