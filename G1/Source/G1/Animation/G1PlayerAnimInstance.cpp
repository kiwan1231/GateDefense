// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/G1PlayerAnimInstance.h"
#include "Character/G1Character.h"
#include "GameFramework/CharacterMovementComponent.h"

UG1PlayerAnimInstance::UG1PlayerAnimInstance(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UG1PlayerAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
}

void UG1PlayerAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	FVector LocalVelocity = Character->GetTransform().InverseTransformVectorNoScale(Velocity);
	UE_LOG(LogTemp, Warning, TEXT("Test Log %s"), *LocalVelocity.ToString());

	bShouldMove = (GroundSpeed > 3.f && MovementComponent->GetCurrentAcceleration() != FVector::ZeroVector);
	bIsFalling = MovementComponent->IsFalling();

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
