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
}
