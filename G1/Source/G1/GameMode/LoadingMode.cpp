// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/LoadingMode.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/TimerHandle.h"

ALoadingMode::ALoadingMode(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;
}

void ALoadingMode::BeginPlay()
{
	Super::BeginPlay();

	TempLoadingTime = TempLoadingMaxTime;

	LoadingDesc = FText::FromString(TEXT("test123.."));
}

void ALoadingMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TempLoadingTime = FMath::Clamp(TempLoadingTime - DeltaTime, 0, TempLoadingMaxTime);

	int progress = ((TempLoadingMaxTime - TempLoadingTime) / TempLoadingMaxTime) * 100;

	LoadingDesc = FText::Format(FText::FromString("Loading... {0}%"),progress);

	if (progress == 100 && !bLoadingComplete)
	{
		bLoadingComplete = true;

		// 0.5초 뒤 전환
		GetWorldTimerManager().SetTimer(
			TimerHandle,
			this,
			&ALoadingMode::MoveToNextLevel,
			0.5f,
			false
		);
	}
}

void ALoadingMode::MoveToNextLevel()
{
	if (bMoveStarted) return;

	bMoveStarted = true;

	UGameplayStatics::OpenLevel(this, NextLevelName);
}
