// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Item/DropItem/G1DropItemNameWidget.h"
#include "Components/TextBlock.h"

#include "Item/G1EquipmentItem.h"
#include "Data/G1ItemData.h"
#include "System/G1AssetManager.h"

UG1DropItemNameWidget::UG1DropItemNameWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UG1DropItemNameWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UG1DropItemNameWidget::SetItem(const FName ItemID)
{
	CurrentItemID = ItemID;
	const UG1ItemData* ItemData = UG1AssetManager::GetAssetByName<UG1ItemData>("Item_Weapon");
	if (ItemData == nullptr)
	{
		return;
	}
	const FG1ItemInfo* Info = ItemData->FindItemInfo(ItemID);
	if (Info == nullptr)
	{
		return;
	}

	ItemName->SetText(Info->ItemName);
	ItemName->SetColorAndOpacity(UG1ItemData::GetRarityColor(Info->ItemRarity));
}
