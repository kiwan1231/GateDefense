// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/G1PlayerController.h"
#include "Character/G1Player.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Kismet/KismetMathLibrary.h"
#include "System/G1AssetManager.h"
#include "Data/G1PlayerInputData.h"
#include "Utility/G1GameplayTags.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "NiagaraFunctionLibrary.h"

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

			auto JumpAction = InputData->FindInputActionByTag(G1GameplayTags::Input_Action_Jump);
			EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ThisClass::Input_Jump);

			auto HitTargetAction = InputData->FindInputActionByTag(G1GameplayTags::Input_Action_HitTarget);
			EnhancedInputComponent->BindAction(HitTargetAction, ETriggerEvent::Triggered, this, &ThisClass::Input_HitTarget);
		}
	}
}

void AG1PlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	UpdateMovePoint(DeltaTime);

}

void AG1PlayerController::StopMovement()
{
	Super::StopMovement();

	SetCharacterState(ECharacterState::Idle);
	CachedDestination = FVector::ZeroVector;
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
	FRotator YawRot(0.f, CamRot.Yaw, 0.f);

	if (MovementVector.X != 0)
	{
		FVector Forward = FRotationMatrix(YawRot).GetUnitAxis(EAxis::X);
		//GetPawn()->AddActorWorldOffset(Forward * 10.0f * MovementVector.X);
		GetPawn()->AddMovementInput(Forward, MovementVector.X);
	}

	if (MovementVector.Y != 0)
	{
		FVector Right = FRotationMatrix(YawRot).GetUnitAxis(EAxis::Y);
		//GetPawn()->AddActorWorldOffset(Right * 10.0f * MovementVector.Y);
		GetPawn()->AddMovementInput(Right, MovementVector.Y);
	}

	SetCharacterState(ECharacterState::MoveDirection);
	CachedDestination = FVector::ZeroVector;
}

void AG1PlayerController::Input_Turn(const FInputActionValue& InputValue)
{
}

void AG1PlayerController::Input_Jump(const FInputActionValue& InputValue)
{
	if (AG1Character* MyCharacter = Cast<AG1Character>(GetPawn()))
	{
		MyCharacter->Jump();
	}
}

void AG1PlayerController::Input_Attack(const FInputActionValue& InputValue)
{
}

void AG1PlayerController::Input_HitTarget(const FInputActionValue& InputValue)
{
	// We look for the location in the world where the player has pressed the input
	FHitResult Hit;
	bool bHitSuccessful = GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, OUT Hit);

	// If we hit a surface, cache the location
	if (false == bHitSuccessful)
	{
		return;
	}

	// Move towards mouse pointer or touch
	if (GetPawn() != nullptr)
	{
		SetCharacterState(ECharacterState::MovePoint);
		CachedDestination = Hit.Location;
		// We move there and spawn some particles

		if (FXCursor)
		{
			UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, CachedDestination);
			UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, FXCursor, CachedDestination, FRotator::ZeroRotator, FVector(1.f, 1.f, 1.f), true, true, ENCPoolMethod::None, true);
		}
	}
}

void AG1PlayerController::UpdateMovePoint(float DeltaTime)
{
	if (GetCharacterState() != ECharacterState::MovePoint)
	{
		return;
	}

	APawn* ControlledPawn = GetPawn();
	if (ControlledPawn == nullptr)
	{
		StopMovement();
		return;
	}

	FVector Direction = CachedDestination - R1Player->GetActorLocation();
	Direction.Z = 0;
	if (Direction.Length() <= 100)
	{
		StopMovement();
		return;
	}

	FVector MoveDirection = (CachedDestination - ControlledPawn->GetActorLocation()).GetSafeNormal();
	ControlledPawn->AddMovementInput(MoveDirection, 10, false);
}

ECharacterState AG1PlayerController::GetCharacterState()
{
	return (R1Player) ? R1Player->State : ECharacterState::None;
}

void AG1PlayerController::SetCharacterState(ECharacterState InState)
{
	if (R1Player)
	{
		R1Player->State = InState;
	}
}
