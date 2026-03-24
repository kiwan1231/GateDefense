// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/G1Character.h"
#include "Utility/G1GameplayTags.h"


#include "G1Player.generated.h"

struct FInputActionValue;

/**
 * 
 */
UCLASS()
class G1_API AG1Player : public AG1Character
{
	GENERATED_BODY()
	
public:
	AG1Player();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<class USpringArmComponent> SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<class UCameraComponent> Camera;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class USphereComponent> CameraPivotSphere;

private:
	FVector SpringArmSocketOffset;
	FVector SpringArmTargetOffset;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void PossessedBy(AController* NewController) override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void HandleGameplayEvent(UAnimMontage* Montage, FGameplayTag EventTag, ECharacterAnimNotiType EventType);

	virtual void UpdateCamera(float DeltaTime);

protected: // interface
	virtual void InitAbilitySystem() override;

private:
	FVector GetSpringArmEndLocation();
};
