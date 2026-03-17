// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "G1ItemDefine.h"

#include "G1Item2DInstance.generated.h"

/**
 * 
 */
UCLASS()
class G1_API UG1Item2DInstance : public UObject
{
	GENERATED_BODY()
	
public:
	UG1Item2DInstance(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

public:
	void Init(int32 InItemID);

public:
	UPROPERTY()
	int32 ItemID = 0;
	UPROPERTY()
	EItemRarity ItemRarity = EItemRarity::Common;
};
