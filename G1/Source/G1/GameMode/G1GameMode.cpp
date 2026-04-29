// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/G1GameMode.h"
#include "GameFramework/GameStateBase.h"
#include "Player/G1PlayerState.h"
#include "Character/G1Player.h"
#include "Utility/G1LogChannels.h"
#include "System/G1AssetManager.h"
#include "Data/G1GameModeData.h"
#include "Character/G1Monster.h"
#include "Kismet/GameplayStatics.h"

AG1GameMode::AG1GameMode()
	: Super()
{
	PrimaryActorTick.bCanEverTick = true;
	ModeType = EGameModeType::None;
}

void AG1GameMode::BeginPlay()
{
	Super::BeginPlay();

	InitEventInstance();

	ChangeState(EGameModeState::Intro);

	ElapsedTime = 0.f;

	APawn* Pawn = UGameplayStatics::GetPlayerPawn(this, 0);
	AG1Character* Player = Cast<AG1Character>(Pawn);
	if (Player)
	{
		Player->OnCharacterDead.AddUObject(this, &AG1GameMode::Delegate_OnCharacterDead);
	}
}

void AG1GameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CheckState(DeltaTime);

	if (ModeState == EGameModeState::Playing)
	{
		ElapsedTime += DeltaTime;

		CheckElapsedTimeEvent(DeltaTime);
	}

	else if (ModeState == EGameModeState::GameOver)
	{

	}

	else if (ModeState == EGameModeState::GameClear)
	{

	}
}

void AG1GameMode::CheckState(float DeltaTime)
{
	if (ModeState == EGameModeState::Intro)
	{
		ChangeState(EGameModeState::Playing);
	}

	else if (ModeState == EGameModeState::Playing)
	{
		APlayerController* PC = GetWorld()->GetFirstPlayerController();
		AG1PlayerState* PS = PC ? Cast<AG1PlayerState>(PC->PlayerState) : nullptr;
		//APlayerController* PC = Cast<APlayerController>(PS->GetOwner());
		if (PC == nullptr)
		{
			UE_LOG(LogG1, Error, TEXT("APlayerController is not Search"));
			return;
		}

		AG1Player* Player = Cast<AG1Player>(PS->GetPawn());
		if (Player == nullptr)
		{
			UE_LOG(LogG1, Error, TEXT("AG1Player is not Search"));
			return;
		}

		if (Player->InDeadState())
		{
			ChangeState(EGameModeState::Outro);
		}
	}
}

void AG1GameMode::ChangeState(EGameModeState State)
{
	ModeState = State;
}

void AG1GameMode::InitEventInstance()
{
	auto GameModeData = UG1AssetManager::GetAssetByName<UG1GameModeData>("GameModeData_Common");

	EventInstanceList.Empty();

	if (GameModeData)
	{
		for (const FEventData& Event : GameModeData->EventDataList)
		{
			EventInstanceList.Emplace(&Event, true);
		}
	}
	else
	{
		UE_LOG(LogG1, Error, TEXT("UG1GameModeData Load Fail"));
	}
}

void AG1GameMode::PlayEventAction(FG1EventInstance* PlayEvent)
{
	return;

	PlayEvent->TriggerCount = 0;

	if (PlayEvent->EventData->Repeat == false)
	{
		PlayEvent->CompleteTrigger = true;
	}

	for (const FEventActionData& Action : PlayEvent->EventData->ActionDataList)
	{
		if (Action.ActionType == EEventActionType::SpawnMonster)
		{
			AG1Monster* Monster = GetWorld()->SpawnActor<AG1Monster>(Action.SpawnMonster, Action.SpawnPos, FRotator::ZeroRotator);
			if (Monster != nullptr)
			{
				Monster->MonsterDropID = Action.SpawnMonsterDropID;
				Monster->OnCharacterDead.AddUObject(this, &AG1GameMode::Delegate_OnCharacterDead);
			}
		}
		else if (Action.ActionType == EEventActionType::RandomSpawnMonster)
		{
			FVector RandomPos = FVector::ZeroVector;

			if (Action.RandomSpawnList.Num() > 0)
			{
				int32 Index = FMath::RandRange(0, Action.RandomSpawnList.Num() - 1);
				RandomPos = Action.RandomSpawnList[Index];
			}

			AG1Monster* Monster = GetWorld()->SpawnActor<AG1Monster>(Action.SpawnMonster, RandomPos, FRotator::ZeroRotator);
			if (Monster != nullptr)
			{
				Monster->MonsterDropID = Action.SpawnMonsterDropID;
				Monster->OnCharacterDead.AddUObject(this, &AG1GameMode::Delegate_OnCharacterDead);
			}
		}
		else if (Action.ActionType == EEventActionType::GameOver)
		{
			OnGameOver.Broadcast(ModeType);
		}
	}
}

void AG1GameMode::CheckElapsedTimeEvent(float DeltaTime)
{
	for (FG1EventInstance& EventInstance : EventInstanceList)
	{
		if (EventInstance.CompleteTrigger)
		{
			continue;
		}

		if (EventInstance.EventData->TriggerType != EEventTriggerType::ElapsedTime)
		{
			continue;
		}

		EventInstance.ElapsedTime += DeltaTime;

		if (EventInstance.EventData->ElapsedTime <= EventInstance.ElapsedTime)
		{
			PlayEventAction(&EventInstance);

			if (EventInstance.EventData->Repeat)
			{
				EventInstance.ElapsedTime -= EventInstance.EventData->ElapsedTime;
			}
		}
	}
}

void AG1GameMode::CheckCharacterDeadEvent(AG1Character* DeadCharacter)
{
	for (FG1EventInstance& EventInstance : EventInstanceList)
	{
		if (EventInstance.CompleteTrigger)
		{
			continue;
		}

		if (DeadCharacter->TeamTag == G1GameplayTags::Team_Monster
				&& EventInstance.EventData->TriggerType != EEventTriggerType::MonsterDeath)
		{
			continue;
		}

		if (DeadCharacter->TeamTag == G1GameplayTags::Team_Player
			&& EventInstance.EventData->TriggerType != EEventTriggerType::PlayerDeath)
		{
			continue;
		}

		EventInstance.TriggerCount += 1;

		if (EventInstance.TriggerCount >= EventInstance.EventData->RequiredTriggerCount)
		{
			PlayEventAction(&EventInstance);
		}
	}
}

void AG1GameMode::Delegate_OnCharacterDead(AG1Character* DeadCharacter)
{
	UE_LOG(LogTemp, Log, TEXT("Delegate_OnCharacterDead !!!"));

	if (DeadCharacter == nullptr)
	{
		return;
	}

	CheckCharacterDeadEvent(DeadCharacter);
}
