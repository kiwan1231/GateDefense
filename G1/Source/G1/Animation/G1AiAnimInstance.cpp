// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/G1AiAnimInstance.h"

UG1AiAnimInstance::UG1AiAnimInstance(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UG1AiAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
}

void UG1AiAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	bShouldMove = (GroundSpeed > 3.f);

	ForwardState = (Velocity.X == 0) ? 0 : (Velocity.X > 0) ? 1 : -1;
	RightState = (Velocity.Y == 0) ? 0 : (Velocity.Y > 0) ? 1 : -1;

	if (ForwardState == 0 && RightState == 0)
	{
		AnimState = ECharacterAnimState::Idle;
	}
	else if (ForwardState != 0 && RightState != 0)
	{
		AnimState = ECharacterAnimState::Diagonal;
	}
	else if (ForwardState != 0)
	{
		AnimState = ECharacterAnimState::Forward;
	}
	else if (RightState != 0)
	{
		AnimState = ECharacterAnimState::Right;
	}
}
