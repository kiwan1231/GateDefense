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
	EItemType ItemType = EItemType::None;

	UPROPERTY(EditDefaultsOnly)
	EItemRarity ItemRarity = EItemRarity::Common;

	UPROPERTY(EditDefaultsOnly)
	FText ItemName;

	UPROPERTY(EditDefaultsOnly)
	FText ItemDesc;

	UPROPERTY(EditDefaultsOnly)
	bool Stackable;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AG1EquipmentItem> EquipmentStaticMesh;

	// 드랍(픽업)용 액터 클래스 — 월드에 떠있는 픽업을 위한 클래스
	UPROPERTY(EditDefaultsOnly, Category = "Drop")
	TSubclassOf<class AG1DropItem> DropStaticMeshClass;

	UPROPERTY(EditDefaultsOnly)
	TSoftObjectPtr<UTexture2D> IconImage;

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
	static FLinearColor GetRarityColor(EItemRarity Rarity);
public:
	UPROPERTY(EditDefaultsOnly)
	TArray<FG1ItemInfo> ItemDataList;
};
