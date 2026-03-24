// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "G1CharacterDefine.h"

#include "G1CharacterConditionData.generated.h"

USTRUCT()
struct FG1CharacterConditionData
{
	GENERATED_BODY()

public:
	EConditionType Type;

	float DurationTime; // -1이면 무한

	float float1;

	int int1;
};
