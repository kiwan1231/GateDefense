// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"


#include "G1InventorySubsystem.generated.h"

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

class UG1Item2DInstance;
/**
 * 
 */
UCLASS()
class G1_API UG1InventorySubsystem : public UWorldSubsystem
{
	GENERATED_BODY()
	
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	virtual void Deinitialize() override;

	//const TArray<TObjectPtr<UG1Item2DInstance>>& GetItems() { return Items; }

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FIntPoint  InventorySize;

	// 실제 데이터 (SizeX * SizeY)
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FG1InventoryItemData> ItemDatas;

public:
	//int32 GetIndex(const int32 X, const int32 Y) const;// 인덱스 계산 함수
	//FG1InventoryItemData* GetItem(const int32 X, const int32 Y);// 특정 위치 접근
	const TArray<FG1InventoryItemData>& GetItemDatas() const { return ItemDatas; }
	const FIntPoint& GetInventorySize() const { return InventorySize; }

//protected:
//	TArray<TObjectPtr<UG1Item2DInstance>> Items;
};
