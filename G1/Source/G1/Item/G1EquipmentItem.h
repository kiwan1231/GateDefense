// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/G1Item3DInstance.h"
#include "G1EquipmentItem.generated.h"

UCLASS()
class G1_API AG1EquipmentItem : public AG1Item3DInstance
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AG1EquipmentItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};