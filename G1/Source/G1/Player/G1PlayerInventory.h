// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Data/G1ItemData.h"
#include "Item/G1ItemDefine.h"

#include "G1PlayerInventory.generated.h"


class UG1Item2DInstance;
class AG1Player;

DECLARE_MULTICAST_DELEGATE_TwoParams(FOnCreateInventoryItem, AG1Player*, FIntPoint);
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnRemoveInventoryItem, AG1Player*, FIntPoint);
DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnInventoryItemCount, AG1Player*, FIntPoint, int32);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class G1_API UG1InventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UG1InventoryComponent();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FIntPoint  InventorySize;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<TObjectPtr<UG1Item2DInstance>> InventoryItems;

private:
	AG1Player* G1Player;
	class AG1PlayerController* PlayerController;

public:
	void InitPlayerInventory(AG1Player* _G1Player, class AG1PlayerController* _PlayerController);

	bool InventoryAddItem(const FName ItemID, const int32 Count);
	void SlotAddItem(const int32 X, const int32 Y, const FName ItemID, const int32 Count);
	void RemoveItem(const FName ItemID, const int32 Count);
	void RemoveItem(const int32 X, const int32 Y, const int32 Count);
	void MoveItem(const FIntPoint& PrePos, const FIntPoint& MovePos);

public:
	int32 GetIndex(const int32 X, const int32 Y);// 인덱스 계산 함수
	TObjectPtr<UG1Item2DInstance> GetItem(const int32 X, const int32 Y);// 특정 위치 접근
	TArray<TObjectPtr<UG1Item2DInstance>> GetInventoryItems() const;
	const FIntPoint& GetInventorySize() const;

public:
	FOnCreateInventoryItem OnCreateInventoryItem;
	FOnRemoveInventoryItem OnRemoveInventoryItem;
	FOnInventoryItemCount OnInventoryItemCount;
};