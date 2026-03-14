// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Item/G1ItemDefine.h"

#include "G1ItemData.generated.h"

USTRUCT()
struct FG1ItemInfo
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly)
	FName ItemID;

	UPROPERTY(EditDefaultsOnly)
	EItemType ItemType;

	UPROPERTY(EditDefaultsOnly)
	EItemRarity ItemRarity;

	UPROPERTY(EditDefaultsOnly)
	bool Stackable;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AG1EquipmentItem> EquipmentStaticMesh;

	/*UPROPERTY(EditDefaultsOnly)
	UStaticMesh* DropStaticMesh;*/

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UGameplayEffect> ItemEffect;
};

/**
 * 
 */
UCLASS()
class G1_API UG1ItemData : public UDataAsset
{
	GENERATED_BODY()
	
public:
	const FG1ItemInfo* FindItemInfo(const FName& ItemID) const;

public:
	UPROPERTY(EditDefaultsOnly)
	TArray<FG1ItemInfo> ItemDataList;
};
