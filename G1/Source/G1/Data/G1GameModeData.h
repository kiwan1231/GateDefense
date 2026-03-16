// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"

#include "G1GameModeData.generated.h"

UENUM(BlueprintType)
enum class EGameModeEventTrigger : uint8
{
	None = 0,
	ElapsedTime,
	MonsterKill,
	BossKill,
	PlayerEnterArea,
};

UENUM(BlueprintType)
enum class EGameModeEventAction : uint8
{
	None = 0,
	SpawnMonster,
	SpawnBoss,
	ClearGame,
	ActiveTrigger,
};

USTRUCT()
struct FGameModeEvent
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly)
	FName EventID;

	/// Trigger
	UPROPERTY(EditAnywhere, meta = (EditCondition = "EventType == EGameModeEventTrigger::ElapsedTime"))
	float ElapsedTime;

	UPROPERTY(EditAnywhere, meta = (EditCondition = "EventType == EGameModeEventTrigger::BossKill"))
	FName BossMonsterID;
};

/**
 * 
 */
UCLASS()
class G1_API UG1GameModeData : public UDataAsset
{
	GENERATED_BODY()
	
//public:
//	const FG1ItemInfo* FindItemInfo(const FName& ItemID) const;
//
//public:
//	UPROPERTY(EditDefaultsOnly)
//	TArray<FG1ItemInfo> ItemDataList;
};
