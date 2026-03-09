// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "G1AIController.generated.h"

/**
 * 
 */
UCLASS()
class G1_API AG1AIController : public AAIController
{
	GENERATED_BODY()
	
public:
	AG1AIController(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	virtual void OnPossess(APawn* InPawn) override;

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
};
