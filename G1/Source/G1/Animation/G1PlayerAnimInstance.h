// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/G1AnimInstance.h"
#include "G1PlayerAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class G1_API UG1PlayerAnimInstance : public UG1AnimInstance
{
	GENERATED_BODY()
	
public:
	UG1PlayerAnimInstance(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

};
