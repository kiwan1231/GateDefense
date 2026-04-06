// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/G1ItemData.h"

const FG1ItemInfo* UG1ItemData::FindItemInfo(const FName& ItemID) const
{
	for (const FG1ItemInfo& Data : ItemDataList)
	{
		if (Data.ItemID.IsEqual(ItemID))
		{
			return &Data;
		}
	}

	return nullptr;
}

FLinearColor UG1ItemData::GetRarityColor(EItemRarity Rarity)
{
	switch (Rarity)
	{
	case EItemRarity::Common:
		return FLinearColor(1.f, 1.f, 1.f); // Èò»ö

	case EItemRarity::UnCommon:
		return FLinearColor(0.1f, 1.f, 0.1f); // ÃÊ·Ï

	case EItemRarity::Rare:
		return FLinearColor(0.0f, 0.4f, 1.f); // ÆÄ¶û

	case EItemRarity::Epic:
		return FLinearColor(0.6f, 0.2f, 1.f); // º¸¶ó

	case EItemRarity::Legendary:
		return FLinearColor(1.f, 0.5f, 0.0f); // ÁÖÈ²

	case EItemRarity::Unique:
		return FLinearColor(1.f, 0.9f, 0.2f); // ±Ý»ö ´À³¦

	default:
		return FLinearColor::White;
	}
}
