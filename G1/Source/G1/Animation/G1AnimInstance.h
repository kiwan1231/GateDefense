// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Animation/G1AnimDefine.h"

#include "G1AnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class G1_API UG1AnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UG1AnimInstance(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

protected:
	virtual bool IsInit();

public:
	virtual UAnimMontage* GetHitAnimMontage() const;
	virtual UAnimMontage* GetDeathAnimMontage() const;

protected:
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<class AG1Character> Character;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<class UCharacterMovementComponent> MovementComponent;

protected:
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	FVector Velocity = FVector::ZeroVector;

	UPROPERTY(BlueprintReadOnly)
	float GroundSpeed = 0.f;

	UPROPERTY(BlueprintReadOnly)
	bool bShouldMove = false;

	UPROPERTY(BlueprintReadOnly)
	ECharacterAnimState AnimState;

	UPROPERTY(BlueprintReadOnly)
	bool bIsFalling = false;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UAnimMontage> HitMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UAnimMontage> DeathMontage;

public:
	UPROPERTY(BlueprintReadOnly)
	bool EnableAnimInstance = true;

	UPROPERTY(BlueprintReadOnly)
	float ForwardState = 0.f;		// -1 후진, 0, 1 전진
	UPROPERTY(BlueprintReadOnly)
	float RightState = 0.f;			// -1 왼쪽, 0 , 1 오른쪽

};
