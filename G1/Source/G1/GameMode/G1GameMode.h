// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "G1GameModeDefine.h"


#include "G1GameMode.generated.h"

/**
 * 
 */

class AG1Character;
struct FEventData;

USTRUCT()
struct FG1EventInstance
{
	GENERATED_BODY()

public:
	FG1EventInstance()
	{

	}

	FG1EventInstance(const FEventData* _EventData, bool _EnabledTrigger)
		: EventData(_EventData)
		, EnabledTrigger(_EnabledTrigger)
		, CompleteTrigger(false)
	{

	}

public:
	const FEventData* EventData = nullptr;

	UPROPERTY(VisibleAnywhere)
	bool EnabledTrigger = false;

	UPROPERTY(VisibleAnywhere)
	bool CompleteTrigger = false;

	UPROPERTY(VisibleAnywhere)
	int TriggerCount = 0;
};

UCLASS()
class G1_API AG1GameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	AG1GameMode();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	virtual void CheckState(float DeltaTime);
	virtual void ChangeState(EGameModeState State);

public:
	virtual void InitEventInstance();
	virtual void PlayEventAction(FG1EventInstance* PlayEvent);
	virtual void CheckElapsedTimeEvent();
	virtual void CheckCharacterDeadEvent(AG1Character* DeadCharacter);

public:/// Delegate 구독 함수
	virtual void Delegate_OnCharacterDead(AG1Character* DeadCharacter);

public:
	UPROPERTY(BlueprintReadWrite, Category = ModeBase)
	EGameModeState ModeState;

	UPROPERTY(BlueprintReadWrite, Category = ModeBase)
	float ElapsedTime = 0.f;

	UPROPERTY()
	class UG1GameModeData* GameModeData = nullptr;

	UPROPERTY()
	TArray<FG1EventInstance> EventInstanceList;
};
