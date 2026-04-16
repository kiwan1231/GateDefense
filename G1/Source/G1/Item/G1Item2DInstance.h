// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "G1ItemDefine.h"

#include "G1Item2DInstance.generated.h"

class UG1ItemData;
/**
 * 
 */
UCLASS()
class G1_API UG1Item2DInstance : public UObject
{
	GENERATED_BODY()
	
public:
	UG1Item2DInstance(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

public:
	void Init(EItemSlotType _ItemSlotType, int32 _X, int32 _Y, FName _ItemID, int32 _Count, UG1ItemData* _ItemData);

public:
	UPROPERTY()
	EItemSlotType ItemSlotType = EItemSlotType::None;
	UPROPERTY()
	FIntPoint InventorySlotPos;
	UPROPERTY()
	FName ItemID = NAME_None;
	UPROPERTY()
	EItemType ItemType = EItemType::None;
	UPROPERTY()
	EItemRarity ItemRarity = EItemRarity::Common;
	UPROPERTY()
	int32 Count = 1;
	UPROPERTY()
	bool bIsStackable = false;
	UPROPERTY()
	TSoftObjectPtr<UTexture2D> IconImage;
};
