// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTS_UpdateBlackboard.generated.h"

/**
 * 
 */
UCLASS()
class G1_API UBTS_UpdateBlackboard : public UBTService
{
	GENERATED_BODY()
	
public:
	UBTS_UpdateBlackboard();

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FBlackboardKeySelector DeadStateKey;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FBlackboardKeySelector EnableMoveKey;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FBlackboardKeySelector EnableAttackKey;
};
