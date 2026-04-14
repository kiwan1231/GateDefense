// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/G1Character.h"
#include "Utility/G1GameplayTags.h"

#include "G1Player.generated.h"

struct FInputActionValue;
struct FG1InventoryItemData;

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

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DropItemCheckDistance;

private:
	TObjectPtr<class AG1PlayerController> Controller;

	FVector SpringArmSocketOffset;
	FVector SpringArmTargetOffset;

	TObjectPtr<class AG1DropItem> NearestDropItem;
	TObjectPtr<class UG1InventoryComponent> Inventory;

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

public:
	virtual void OnDamaged(int32 Damage, TObjectPtr<AG1Character> Attacker, const FHitResult& SweepResult) override;

	virtual int OnItemPickUp();

public:
	const TObjectPtr<class UG1InventoryComponent>& GetInventoryComponent() const;

protected: // interface
	virtual void InitAbilitySystem() override;

private:
	FVector GetSpringArmEndLocation();
	float GetHpRatio() const;
	void FindNearestDropItem();
};
