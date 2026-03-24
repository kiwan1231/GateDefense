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
}

void UG1AnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (IsInit() == false)
	{
		return;
	}

	EnableAnimInstance = AnimState != ECharacterAnimState::Dead;

	Velocity = MovementComponent->Velocity;
	GroundSpeed = Velocity.Size2D();
}

bool UG1AnimInstance::IsInit()
{
	if (Character == nullptr)
	{
		Character = Cast<AG1Character>(TryGetPawnOwner());
	}

	if (Character != nullptr && MovementComponent == nullptr)
	{
		MovementComponent = Character->GetCharacterMovement();
	}

	return (Character != nullptr || MovementComponent != nullptr);
}

UAnimMontage* UG1AnimInstance::GetHitAnimMontage() const
{
	return HitMontage;
}

UAnimMontage* UG1AnimInstance::GetDeathAnimMontage() const
{
	return DeathMontage;
}
