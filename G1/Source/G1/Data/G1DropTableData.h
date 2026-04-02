// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "G1ItemData.h"
#include "Item/G1ItemDefine.h"

#include "G1DropTableData.generated.h"

USTRUCT(BlueprintType)
struct FG1DropEntry
{
	GENERATED_BODY()

public:
	// 드랍될 아이템의 ID (UG1ItemData의 ItemID와 일치해야 함)
	UPROPERTY(EditDefaultsOnly, Category = "Drop")
	FName ItemID;

	// 드랍 확률 (0.0 - 1.0)
	UPROPERTY(EditDefaultsOnly, Category = "Drop", meta = (ClampMin = "0.0", ClampMax = "1.0"))
	float DropChance = 0.0f;

	// 드랍시 랜덤 개수 범위 (포함)
	UPROPERTY(EditDefaultsOnly, Category = "Drop", meta = (ClampMin = "0"))
	int32 MinCount = 1;

	UPROPERTY(EditDefaultsOnly, Category = "Drop", meta = (ClampMin = "0"))
	int32 MaxCount = 1;
};

USTRUCT(BlueprintType)
struct FMonsterDropRow
{
	GENERATED_BODY()

public:
	// 몬스터 식별자 (예: "Monster_Skeleton")
	UPROPERTY(EditDefaultsOnly, Category = "Drop")
	FName MonsterDropID;

	// 해당 몬스터가 드랍할 수 있는 아이템 목록
	UPROPERTY(EditDefaultsOnly, Category = "Drop")
	TArray<FG1DropEntry> DropEntries;
};

USTRUCT(BlueprintType)
struct FG1DropResult
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, Category = "Drop")
	FName ItemID;

	UPROPERTY(VisibleAnywhere, Category = "Drop")
	int32 Count = 0;
};

/**
 * 몬스터별 아이템 드랍 정보를 저장하는 DataAsset
 */
UCLASS()
class G1_API UG1DropTableData : public UDataAsset
{
	GENERATED_BODY()

public:
	// 몬스터별 드랍 테이블(에디터에서 편집)
	UPROPERTY(EditDefaultsOnly, Category = "Drop")
	TArray<FMonsterDropRow> DropTable;

	// MonsterID에 해당하는 드랍 엔트리 포인터를 반환(없으면 nullptr)
	const TArray<FG1DropEntry>* FindDropEntries(const FName& MonsterDropID) const;

	// 확률에 따라 드랍 결과를 채움(빈 배열로 반환 가능)
	void RollDrops(const FName& MonsterDropID, TArray<FG1DropResult>& OutResults, float RandomSeed = -1.0f) const;
};