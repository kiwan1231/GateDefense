// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EItemType : uint8
{
	None,
	Equipment,
	Consumable,
};

UENUM(BlueprintType)
enum class EItemRarity : uint8
{
	Common,
	UnCommon,
	Rare,
	Epic,
	Legendary,
	Unique,
};

UENUM(BlueprintType)
enum class EEquipmentType : uint8
{
	None,
	Weapon,
};