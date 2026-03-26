// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTD_CheckBlackboardByBool.generated.h"

/**
 * 
 */
UCLASS()
class G1_API UBTD_CheckBlackboardByBool : public UBTDecorator
{
	GENERATED_BODY()
	
public:
	UBTD_CheckBlackboardByBool();

protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FBlackboardKeySelector BoolValueKey;
};
