// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/G1PlayerInventory.h"
#include "System/G1AssetManager.h"
#include "Data/G1ItemData.h"
#include "Item/G1Item2DInstance.h"

#include "Subsystems/SubsystemBlueprintLibrary.h"
#include "Item/G1InventorySubsystem.h"
#include "Item/G1ItemDefine.h"

#include "Character/G1Player.h"
#include "Player/G1PlayerController.h"

UG1InventoryComponent::UG1InventoryComponent()
	: Super()
{
	InventorySize.X = 10;
	InventorySize.Y = 5;
}

void UG1InventoryComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UG1InventoryComponent::InitPlayerInventory(AG1Player* _G1Player, AG1PlayerController* _PlayerController)
{
	G1Player = _G1Player;
	PlayerController = _PlayerController;

	auto ItemData = UG1AssetManager::GetAssetByName<UG1ItemData>("Item_Weapon");

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
		InventoryItems[i]->Init(EItemSlotType::Inventory, i % InventorySize.X, i / InventorySize.X, ItemDatas[i].ItemID, ItemDatas[i].Count, ItemData);
	}
}

bool UG1InventoryComponent::InventoryAddItem(const FName ItemID, const int32 Count)
{
	/// 중첩이 아닌경우 추가될 위치 저장
	int X = 0; int Y = 0;
	bool bFoundStackable = false;

	for (int i = 0; i < InventoryItems.Num(); i++)
	{
		if (InventoryItems[i] == nullptr)
		{
			if (bFoundStackable == false)
			{
				X = i % InventorySize.X;
				Y = i / InventorySize.X;
				bFoundStackable = true;
			}
		}
		else
		{
			if (InventoryItems[i]->bIsStackable && InventoryItems[i]->ItemID.IsEqual(ItemID))
			{
				InventoryItems[i]->Count += Count;
				return true;
			}
		}
	}

	if (bFoundStackable)
	{
		SlotAddItem(X, Y, ItemID, Count);
		return true;
	}
	else
	{
		return false;
	}
	return false;
}

void UG1InventoryComponent::SlotAddItem(const int32 X, const int32 Y, const FName ItemID, const int32 Count)
{
	auto ItemData = UG1AssetManager::GetAssetByName<UG1ItemData>("Item_Weapon");

	if (ItemData == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("UG1InventoryComponent::AddItem: ItemData is null"));
		return;
	}

	int32 Index = GetIndex(X, Y);

	if (InventoryItems[Index] == nullptr)
	{
		InventoryItems[Index] = NewObject<UG1Item2DInstance>(this);
		InventoryItems[Index]->Init(EItemSlotType::Inventory, X, Y, ItemID, Count, ItemData);
		OnCreateInventoryItem.Broadcast(G1Player, InventoryItems[Index]->InventorySlotPos);
	}
	else if (InventoryItems[Index]->ItemID.IsEqual(ItemID) && InventoryItems[Index]->bIsStackable)
	{
		InventoryItems[Index]->Count += Count;
		OnInventoryItemCount.Broadcast(G1Player, InventoryItems[Index]->InventorySlotPos, InventoryItems[Index]->Count);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("UG1InventoryComponent::AddItem: Slot (%d, %d) is occupied by a different item"), X, Y);
	}
}

void UG1InventoryComponent::RemoveItem(const FName ItemID, const int32 Count)
{
	auto ItemData = UG1AssetManager::GetAssetByName<UG1ItemData>("Item_Weapon");

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
				OnInventoryItemCount.Broadcast(G1Player, InventoryItems[i]->InventorySlotPos, InventoryItems[i]->Count);
			}
			else
			{
				auto RemovedItemPos = InventoryItems[i]->InventorySlotPos;
				InventoryItems[i] = nullptr;
				OnRemoveInventoryItem.Broadcast(G1Player, RemovedItemPos);
			}

			break;
		}
	}
}

void UG1InventoryComponent::RemoveItem(const int32 X, const int32 Y, const int32 Count)
{
	auto ItemData = UG1AssetManager::GetAssetByName<UG1ItemData>("Item_Weapon");

	if (ItemData == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("UG1InventoryComponent::RemoveItem: ItemData is null"));
		return;
	}

	int32 Index = GetIndex(X, Y);

	if (InventoryItems[Index]->Count > Count)
	{
		InventoryItems[Index]->Count -= Count;
		OnInventoryItemCount.Broadcast(G1Player, InventoryItems[Index]->InventorySlotPos, InventoryItems[Index]->Count);
	}
	else
	{
		auto RemovedItemPos = InventoryItems[Index]->InventorySlotPos;
		InventoryItems[Index] = nullptr;
		OnRemoveInventoryItem.Broadcast(G1Player, RemovedItemPos);
	}
}

void UG1InventoryComponent::MoveItem(const FIntPoint& PrePos, const FIntPoint& MovePos)
{
	int32 PreIndex = GetIndex(PrePos.X, PrePos.Y);
	int32 MoveIndex = GetIndex(MovePos.X, MovePos.Y);

	if (InventoryItems[PreIndex] == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("UG1InventoryComponent::MoveItem: No item at PrePos (%d, %d)"), PrePos.X, PrePos.Y);
		return;
	}

	UG1Item2DInstance* FromItem = InventoryItems[PreIndex];
	UG1Item2DInstance* ToItem = InventoryItems[MoveIndex];

	// 1. 이동 위치가 비어있는 경우
	if (ToItem == nullptr)
	{
		InventoryItems[MoveIndex] = FromItem;
		InventoryItems[PreIndex] = nullptr;

		FromItem->InventorySlotPos = MovePos;

		OnRemoveInventoryItem.Broadcast(G1Player, PrePos);
		OnCreateInventoryItem.Broadcast(G1Player, MovePos);
	}
	// 2. 같은 아이템 + 스택 가능
	else if (FromItem->ItemID.IsEqual(ToItem->ItemID) && FromItem->bIsStackable)
	{
		ToItem->Count += FromItem->Count;

		InventoryItems[PreIndex] = nullptr;

		OnRemoveInventoryItem.Broadcast(G1Player, PrePos);
		OnInventoryItemCount.Broadcast(G1Player, MovePos, ToItem->Count);
	}
	// 3. 다른 아이템 → Swap
	else
	{
		InventoryItems[PreIndex] = ToItem;
		InventoryItems[MoveIndex] = FromItem;

		// 위치 갱신
		ToItem->InventorySlotPos = PrePos;
		FromItem->InventorySlotPos = MovePos;

		// UI 갱신
		OnCreateInventoryItem.Broadcast(G1Player, PrePos);
		OnCreateInventoryItem.Broadcast(G1Player, MovePos);
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
