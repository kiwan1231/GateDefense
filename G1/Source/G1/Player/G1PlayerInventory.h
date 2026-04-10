// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Data/G1ItemData.h"
#include "Item/G1ItemDefine.h"

#include "G1PlayerInventory.generated.h"

USTRUCT(BlueprintType)
struct FG1InventoryItemData
{
	GENERATED_BODY()

	UPROPERTY()
	FName ItemID;

	UPROPERTY()
	int32 Count;
};

USTRUCT(BlueprintType)
struct FG1PlayerInventory
{
	GENERATED_BODY()
};