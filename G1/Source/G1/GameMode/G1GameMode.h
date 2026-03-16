// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "G1GameModeDefine.h"


#include "G1GameMode.generated.h"

/**
 * 
 */
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
	UPROPERTY(BlueprintReadWrite, Category = ModeBase)
	EGameModeState ModeState;

	UPROPERTY(BlueprintReadWrite, Category = ModeBase)
	float ElapsedTime;
};
