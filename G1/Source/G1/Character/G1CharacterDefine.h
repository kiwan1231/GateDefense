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
enum class EConditionType : uint8
{
	None,
	Hit,
	HitResistance,
	Stun,
	MoveSlow,
};

USTRUCT()
struct FConditionData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly)
	EConditionType Type;

	UPROPERTY(EditDefaultsOnly)
	float DurationTime; // -1이면 무한

	UPROPERTY(EditDefaultsOnly)
	float float1;

	UPROPERTY(EditDefaultsOnly)
	int int1;
};

//UENUM(BlueprintType)
//enum class ECharacterStateFlag : uint8
//{
//	None UMETA(Hidden),
//	Idle = 1 << 0,
//	ForwardMove = 1 << 1,
//	BackMove = 1 << 2,
//	RightMove = 1 << 3,
//	LeftMove = 1 << 4,
//	Jump = 1 << 5,
//	Fall = 1 << 6,
//	Dead = 1 << 7,
//};
//ENUM_CLASS_FLAGS(ECharacterStateFlag)

UENUM(BlueprintType)
enum class ECharacterAnimNotiType : uint8
{
	None,
	OnQueryOnly,
	NoCollision,
};

#define D(x) if(GEngine) { GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Cyan, x); }