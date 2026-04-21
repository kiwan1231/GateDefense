// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Character/G1CharacterDefine.h"
#include "Utility/G1GameplayTags.h"
#include "GameplayTagContainer.h"
#include "Data/G1PlayerInputData.h"
#include "GameMode/G1GameModeDefine.h"

#include "G1PlayerController.generated.h"

struct FInputActionValue;
class UNiagaraSystem;
class AG1Character;
class AG1Player;


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
	virtual void OnPossess(APawn* InPawn) override;
	virtual void SetupInputComponent() override;
	virtual void PlayerTick(float DeltaTime) override;
	virtual void StopMovement() override;

public:
	virtual void HandleGameplayEvent(FGameplayTag EventTag);

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	float ShortPressThreshold = 0.3f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	TObjectPtr<UNiagaraSystem> FXCursor;

private: // input function
	void Input_Move(const FInputActionValue& InputValue);
	void Input_Move_Complete(const FInputActionValue& InputValue);
	void Input_Jump(const FInputActionValue& InputValue);
	void Input_Turn(const FInputActionValue& InputValue);
	void Input_Attack(const FInputActionValue& InputValue);
	void Input_HitTarget(const FInputActionValue& InputValue);

	void Input_OpenInventory(const FInputActionValue& InputValue);
	void Input_PickUpItem(const FInputActionValue& InputValue);

private:/// tick function
	//void UpdateCharacterState(float DeltaTime);
	void UpdateMovePoint(float DeltaTime);
	void UpdateHighlight();

private:
	ECharacterState GetCharacterState();
	void SetCharacterState(ECharacterState InState);
	bool EnablePlayerInput();

public:/// Delegate 구독 함수
	virtual void Delegate_OnGameOver(EGameModeType GameModeType);

private:
	FVector CachedDestination;
	float FollowTime;

protected:
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<AG1Character> TargetActor;
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<AG1Character> HighlightActor;
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<AG1Player> G1Player;
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<USkeletalMeshComponent> MeshComponent;

public:
	UPROPERTY(BlueprintReadWrite)
	TSubclassOf<class UG1IngameSceneWidget> IngameUIClass;
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<class UG1IngameSceneWidget> IngameUI;

	UPROPERTY(BlueprintReadWrite)
	TSubclassOf<class UG1GameOverSceneWidget> GameOverUIClass;
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<class UG1GameOverSceneWidget> GameOverUI;

	/// DropItem
public:
	UPROPERTY(BlueprintReadWrite)
	TSubclassOf<class UG1DropItemDescWidget> DropItemDescWidgetClass;
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<class UG1DropItemDescWidget> DropItemDescWidget;
	UPROPERTY(BlueprintReadOnly)
	FName DropItemID;

	void ShowDropItemDesc(const FVector& WorldLocation, const FName ItemID);
	void HideDropItemDesc();

public:
	void InitUserInterfaceWidget();

public:
	TObjectPtr<class UG1IngameSceneWidget> GetIngameUI();
};
