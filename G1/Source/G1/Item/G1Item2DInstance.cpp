// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/G1Item2DInstance.h"
#include "Data/G1ItemData.h"

UG1Item2DInstance::UG1Item2DInstance(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}

void UG1Item2DInstance::Init(EItemSlotType _ItemSlotType, int32 _X, int32 _Y, FName _ItemID, int32 _Count, const UG1ItemData* _ItemData)
{
	InventorySlotPos = FIntPoint(_X, _Y);

	ItemID = _ItemID;
	Count = _Count;

	auto ItemInfo = _ItemData->FindItemInfo(_ItemID);
	if (ItemInfo == nullptr)
	{
		ItemSlotType = EItemSlotType::None;
		EquipType = EEquipmentType::None;
		ItemType = EItemType::None;
		ItemRarity = EItemRarity::Common;
		bIsStackable = false;
		IconImage = nullptr;
	}
	else
	{
		ItemSlotType = EItemSlotType::None;
		EquipType = ItemInfo->EquipType;
		ItemType = ItemInfo->ItemType;
		ItemRarity = ItemInfo->ItemRarity;
		bIsStackable = ItemInfo->Stackable;
		IconImage = ItemInfo->IconImage;
	}
}
