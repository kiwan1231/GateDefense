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
