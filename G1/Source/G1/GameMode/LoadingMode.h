// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "LoadingMode.generated.h"

/**
 * 
 */
UCLASS()
class G1_API ALoadingMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	ALoadingMode(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	void MoveToNextLevel();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName NextLevelName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText LoadingDesc;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float TempLoadingTime;

private:
	float TempLoadingMaxTime = 2;
	bool bLoadingComplete = false;
	bool bMoveStarted = false;
	struct FTimerHandle TimerHandle;
};
