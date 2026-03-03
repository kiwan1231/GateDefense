// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/G1PlayerController.h"
#include "Character/G1Player.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Kismet/KismetMathLibrary.h"

AG1PlayerController::AG1PlayerController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
	CachedDestination = FVector::ZeroVector;
	FollowTime = 0.f;
}

void AG1PlayerController::BeginPlay()
{
	Super::BeginPlay();
}

void AG1PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
}

void AG1PlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
}

void AG1PlayerController::HandleGameplayEvent(FGameplayTag EventTag)
{

}

void AG1PlayerController::Input_SetDestination(const FInputActionValue& InputValue)
{
}

void AG1PlayerController::Input_Move(const FInputActionValue& InputValue)
{
	FVector2D MovementVector = InputValue.Get<FVector2D>();

	if (MovementVector.X != 0)
	{
		FRotator Rotator = GetControlRotation();
		FVector Direction = UKismetMathLibrary::GetForwardVector(FRotator(0, Rotator.Yaw, 0));
		GetPawn()->AddMovementInput(Direction, MovementVector.X);
	}

	if (MovementVector.Y != 0)
	{
		FRotator Rotator = GetControlRotation();
		FVector Direction = UKismetMathLibrary::GetRightVector(FRotator(0, Rotator.Yaw, 0));
		GetPawn()->AddMovementInput(Direction, MovementVector.Y);
	}
}

void AG1PlayerController::Input_Turn(const FInputActionValue& InputValue)
{
}

void AG1PlayerController::Input_Jump(const FInputActionValue& InputValue)
{
}

void AG1PlayerController::Input_Attack(const FInputActionValue& InputValue)
{
}

void AG1PlayerController::OnInputStarted()
{
}

void AG1PlayerController::OnSetDestinationTriggered()
{
}

void AG1PlayerController::OnSetDestinationReleased()
{
}

ECharacterState AG1PlayerController::GetCharacterState()
{
	return ECharacterState::None;
}

void AG1PlayerController::SetCharacterState(ECharacterState InState)
{
}
