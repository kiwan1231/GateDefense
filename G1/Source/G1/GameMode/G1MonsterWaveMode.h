// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameMode/G1GameMode.h"
#include "G1MonsterWaveMode.generated.h"

/**
 * 
 */
UCLASS()
class G1_API AG1MonsterWaveMode : public AG1GameMode
{
	GENERATED_BODY()
	
public:
	AG1MonsterWaveMode();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
