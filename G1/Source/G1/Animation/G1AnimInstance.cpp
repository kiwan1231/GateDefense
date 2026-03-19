// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/G1AnimInstance.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Character/G1Character.h"

UG1AnimInstance::UG1AnimInstance(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	AnimState = ECharacterAnimState::None;
}

void UG1AnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	Character = Cast<AG1Character>(TryGetPawnOwner());

	if (Character)
		MovementComponent = Character->GetCharacterMovement();
}

void UG1AnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (Character == nullptr || MovementComponent == nullptr)
		return;

	Velocity = MovementComponent->Velocity;
	GroundSpeed = Velocity.Size2D();

	bShouldMove = (GroundSpeed > 3.f && MovementComponent->GetCurrentAcceleration() != FVector::ZeroVector);
	bIsFalling = MovementComponent->IsFalling();

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
	else if (ForwardState != 0)
	{
		AnimState = ECharacterAnimState::Right;
	}
}
