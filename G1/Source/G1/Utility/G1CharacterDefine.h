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

UENUM(BlueprintType)
enum class ECharacterAnimNotiType : uint8
{
	None,
	OnQueryOnly,
	NoCollision,
};

#define D(x) if(GEngine) { GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Cyan, x); }