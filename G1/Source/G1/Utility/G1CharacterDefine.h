// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class ECreatureState : uint8
{
	None,
	Moving,
	Skill,
	Dead,
};
