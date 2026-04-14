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
	bool IsStackable;

	UPROPERTY()
	int32 Count;
};

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
	int32 SizeX = 5;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 SizeY = 4;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FIntPoint  InventorySize;

	// 실제 데이터 (SizeX * SizeY)
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FG1InventoryItemData> Items;

private:
	class UG1ItemData* ItemData;

public:
	bool PickUpItem(const FName ItemID, const int32 Count);
	void AddItem(const int32 X, const int32 Y, const FName ItemID, const int32 Count);
	void RemoveItem(const FName ItemID, const int32 Count);
	void RemoveItem(const int32 X, const int32 Y, const int32 Count);

public:
	int32 GetIndex(const int32 X, const int32 Y);// 인덱스 계산 함수
	FG1InventoryItemData* GetItem(const int32 X, const int32 Y);// 특정 위치 접근
	const TArray<FG1InventoryItemData>& GetItems() const;
	const FIntPoint& GetInventorySize() const;
};