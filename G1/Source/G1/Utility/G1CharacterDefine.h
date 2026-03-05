// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class ECharacterState : uint8
{
	None,
	Idle,
	MoveDirection,
	MovePoint,
	MoveAttack,
	Skill,
	Dead,
};
