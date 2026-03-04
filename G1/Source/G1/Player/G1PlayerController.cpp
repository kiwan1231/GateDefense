// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/G1PlayerController.h"
#include "Character/G1Player.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Kismet/KismetMathLibrary.h"
#include "System/G1AssetManager.h"
#include "Data/G1PlayerInputData.h"
#include "Utility/G1GameplayTags.h"

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

	if (const UG1PlayerInputData* InputData = UG1AssetManager::GetAssetByName<UG1PlayerInputData>("Input_Common"))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(InputData->InputMappingContext, 0);
		}
	}

	R1Player = Cast<AG1Player>(GetCharacter());
}

void AG1PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (const UG1PlayerInputData* InputData = UG1AssetManager::GetAssetByName<UG1PlayerInputData>("Input_Common"))
	{
		if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent))
		{
			auto MoveAction = InputData->FindInputActionByTag(G1GameplayTags::Input_Action_Move);

			EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ThisClass::Input_Move);
		}
	}
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

	FRotator CamRot = this->PlayerCameraManager->GetCameraRotation();
	FVector Direction = UKismetMathLibrary::GetForwardVector(FRotator(0, CamRot.Yaw, 0));

	if (MovementVector.X != 0)
	{
		GetPawn()->AddMovementInput(Direction, MovementVector.X);
	}

	if (MovementVector.Y != 0)
	{
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
