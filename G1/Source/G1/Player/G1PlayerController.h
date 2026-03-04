// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Utility/G1CharacterDefine.h"
#include "Utility/G1GameplayTags.h"
#include "GameplayTagContainer.h"
#include "Data/G1PlayerInputData.h"

#include "G1PlayerController.generated.h"

struct FInputActionValue;
class UNiagaraSystem;
class G1Character;
class G1Player;


class UInputAction;
class UInputMappingContext;
/**
 * 
 */
UCLASS()
class G1_API AG1PlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AG1PlayerController(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	virtual void PlayerTick(float DeltaTime) override;

public:
	virtual void HandleGameplayEvent(FGameplayTag EventTag);

private:
	void TickCursorTrace();
	void ChaseTargetAndAttack();

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	float ShortPressThreshold = 0.3f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	TObjectPtr<UNiagaraSystem> FXCursor;

private:
	void Input_SetDestination(const FInputActionValue& InputValue);
	void Input_Move(const FInputActionValue& InputValue);
	void Input_Turn(const FInputActionValue& InputValue);
	void Input_Jump(const FInputActionValue& InputValue);
	void Input_Attack(const FInputActionValue& InputValue);

	void OnInputStarted();
	void OnSetDestinationTriggered();
	void OnSetDestinationReleased();

private:
	ECharacterState GetCharacterState();
	void SetCharacterState(ECharacterState InState);

private:
	FVector CachedDestination;
	float FollowTime;
	bool bMousePressed = false;

protected:
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<class AG1Character> TargetActor;
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<class AG1Character> HighlightActor;
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<class AG1Player> R1Player;

};
