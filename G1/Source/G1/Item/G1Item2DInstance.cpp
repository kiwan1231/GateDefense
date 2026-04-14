// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/G1Item2DInstance.h"
#include "Data/G1ItemData.h"

UG1Item2DInstance::UG1Item2DInstance(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}

void UG1Item2DInstance::Init(int32 x, int32 y, FName _ItemID, int32 _Count, UG1ItemData* _ItemData)
{
	InventorySlotPos = FIntPoint(x, y);

	ItemID = _ItemID;
	Count = _Count;

	auto ItemInfo = _ItemData->FindItemInfo(_ItemID);
	if (ItemInfo)
	{
		ItemType = ItemInfo->ItemType;
		ItemRarity = ItemInfo->ItemRarity;
		bIsStackable = ItemInfo->Stackable;
		IconImage = ItemInfo->IconImage;
	}
}
