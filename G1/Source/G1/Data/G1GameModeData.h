// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"

#include "G1GameModeData.generated.h"

UENUM(BlueprintType)
enum class EEventTriggerType : uint8
{
	None = 0,
	ElapsedTime,
	PlayerDeath,
	MonsterDeath,
	BossDeath,
	PlayerEnterArea,
};

UENUM(BlueprintType)
enum class EEventActionType : uint8
{
	None = 0,
	SpawnMonster,
	SpawnBoss,
	ClearGame,
	GameOver,
	ActiveTrigger,
};

USTRUCT()
struct FEventActionData
{
	GENERATED_BODY()

public:
	FEventActionData()
		: ActionID(NAME_None)
		, ActionType(EEventActionType::None)
		, SpawnMonster(nullptr)
		, SpawnPos(FVector::ZeroVector)
		, SpawnMonsterDropID(NAME_None)
	{
	}

public:
	UPROPERTY(EditDefaultsOnly)
	FName ActionID = NAME_None;

	UPROPERTY(EditDefaultsOnly)
	EEventActionType ActionType = EEventActionType::None;

public:
	/// Action
	UPROPERTY(EditAnywhere, meta = (EditCondition = "ActionType == EEventActionType::SpawnMonster"))
	TSubclassOf<class AG1Monster> SpawnMonster;
	UPROPERTY(EditAnywhere, meta = (EditCondition = "ActionType == EEventActionType::SpawnMonster"))
	FVector SpawnPos = FVector::ZeroVector;
	UPROPERTY(EditAnywhere, meta = (EditCondition = "ActionType == EEventActionType::SpawnMonster"))
	FName SpawnMonsterDropID = NAME_None;
};

USTRUCT()
struct FEventData
{
	GENERATED_BODY()

public:
	FEventData()
		: EventID(NAME_None)
		, TriggerType(EEventTriggerType::None)
		, Repeat(false)
		, RequiredTriggerCount(1)
		, ElapsedTime(0.f)
	{
	}

public:
	UPROPERTY(EditDefaultsOnly)
	FName EventID = NAME_None;

	UPROPERTY(EditDefaultsOnly)
	EEventTriggerType TriggerType = EEventTriggerType::None;

	UPROPERTY(EditDefaultsOnly)
	bool Repeat = false;

	UPROPERTY(EditDefaultsOnly)
	int RequiredTriggerCount = 1;

public:
	/// Trigger
	UPROPERTY(EditAnywhere, meta = (EditCondition = "TriggerType == EEventTriggerType::ElapsedTime"))
	float ElapsedTime = 0.f;

public:
	/// Action
	UPROPERTY(EditDefaultsOnly)
	TArray<FEventActionData> ActionDataList;

};

/**
 * 
 */
UCLASS()
class G1_API UG1GameModeData : public UDataAsset
{
	GENERATED_BODY()

public:
	const FEventData* FindEventData(const FName& EventID) const;

public:
	UPROPERTY(EditDefaultsOnly)
	TArray<FEventData> EventDataList;

};