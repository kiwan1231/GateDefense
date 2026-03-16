// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/G1GameMode.h"
#include "GameFramework/GameStateBase.h"
#include "Player/G1PlayerState.h"
#include "Character/G1Player.h"
#include "Utility/G1LogChannels.h"

AG1GameMode::AG1GameMode()
	: Super()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AG1GameMode::BeginPlay()
{
	Super::BeginPlay();

	ChangeState(EGameModeState::Intro);

	ElapsedTime = 0.f;
}

void AG1GameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CheckState(DeltaTime);

	if (ModeState == EGameModeState::Playing)
	{
		ElapsedTime += DeltaTime;
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
		AG1PlayerState* PS = GetGameState<AG1PlayerState>();
		if (PS)
		{
			APlayerController* PC = Cast<APlayerController>(PS->GetOwner());
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

			if (Player->IsDeadG1Character())
			{
				ChangeState(EGameModeState::Outro);
			}
		}
	}
}

void AG1GameMode::ChangeState(EGameModeState State)
{
	ModeState = State;
}
