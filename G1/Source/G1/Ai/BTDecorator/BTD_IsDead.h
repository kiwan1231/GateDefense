// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTD_IsDead.generated.h"

/**
 * 
 */
UCLASS()
class G1_API UBTD_IsDead : public UBTDecorator
{
	GENERATED_BODY()
	
public:
	UBTD_IsDead();

protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
