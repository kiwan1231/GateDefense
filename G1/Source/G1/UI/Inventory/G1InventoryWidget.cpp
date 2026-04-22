// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Inventory/G1InventoryWidget.h"
#include "UI/Inventory/G1InventorySlotsWidget.h"
#include "UI/Inventory/G1InventoryEntryWidget.h"

#include "UI/Equip/G1EquipSlotWidget.h"
#include "UI/Equip/G1EquipEntryWidget.h"

#include "Item/G1Item2DInstance.h"

#include "System/G1AssetManager.h"

#include "Character/G1Player.h"
#include "Player/G1PlayerInventory.h"

#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"

#include "GameFramework/GameStateBase.h"

#include "Kismet/GameplayStatics.h"

UG1InventoryWidget::UG1InventoryWidget()
	: Super()
{
}

void UG1InventoryWidget::OnInitInventory(AG1Player* Player)
{
	G1Player = Player;

	if (SlotsWidget == nullptr)
	{
		return;
	}

	SlotsWidget->InitInventorySlots(G1Player);

	G1Player->OnAddEquipment.AddUObject(this, &UG1InventoryWidget::Delegate_OnAddEquipment);
	G1Player->OnRemoveEquipment.AddUObject(this, &UG1InventoryWidget::Delegate_OnRemoveEquipment);

	if (WeaponEntryWidget != nullptr)
	{
		auto Item2DInstance = NewObject<UG1Item2DInstance>(this);
		WeaponEntryWidget->Init(SlotsWidget, Item2DInstance, EEquipmentType::Weapon);
	}
	if (ShieldEntryWidget != nullptr)
	{
		auto Item2DInstance = NewObject<UG1Item2DInstance>(this);
		ShieldEntryWidget->Init(SlotsWidget, Item2DInstance, EEquipmentType::Shield);
	}
	EquipEntryMap.Add(EEquipmentType::Weapon, WeaponEntryWidget);
	EquipEntryMap.Add(EEquipmentType::Shield, ShieldEntryWidget);

	IsInit = true;
}

void UG1InventoryWidget::OnRefreshInventory()
{
	if (IsInit == false)
	{
		return;
	}
}

void UG1InventoryWidget::Delegate_OnAddEquipment(AG1Character* Character, FName ItemID)
{
	auto WeaponItemData = UG1AssetManager::GetAssetByName<UG1ItemData>("Item_Weapon");
	if (WeaponItemData == nullptr)
	{
		UE_LOG(LogTemp, Log, TEXT("Delegate_OnAddEquipment Error, Item_Weapon Asset Load Fail"));
		return;
	}

	const FG1ItemInfo* ItemInfo = WeaponItemData->FindItemInfo(ItemID);
	if (ItemInfo == nullptr || ItemInfo->ItemType != EItemType::Equipment)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s Delegate_OnAddEquipment: No item info found for ItemID %s"), *GetName(), *ItemID.ToString());
		return;
	}

	auto EntryWidget = ItemInfo->EquipType == EEquipmentType::Weapon ? WeaponEntryWidget : ShieldEntryWidget;
	EntryWidget->SetItemInstance(EItemSlotType::Equip, 0, 0, ItemID, 1, WeaponItemData);
}

void UG1InventoryWidget::Delegate_OnRemoveEquipment(AG1Character* Character, EEquipmentType EquipType)
{
	auto WeaponItemData = UG1AssetManager::GetAssetByName<UG1ItemData>("Item_Weapon");
	if (WeaponItemData == nullptr)
	{
		UE_LOG(LogTemp, Log, TEXT("Delegate_OnAddEquipment Error, Item_Weapon Asset Load Fail"));
		return;
	}

	auto EntryWidget = EquipType == EEquipmentType::Weapon ? WeaponEntryWidget : ShieldEntryWidget;
	EntryWidget->SetItemInstance(EItemSlotType::Equip, 0, 0, NAME_None, 0, WeaponItemData);
}
