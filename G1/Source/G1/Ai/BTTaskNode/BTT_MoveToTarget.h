// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTT_MoveToTarget.generated.h"

/**
 * 
 */
UCLASS()
class G1_API UBTT_MoveToTarget : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UBTT_MoveToTarget();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MinDist = 100.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MoveSpeed = 10.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FBlackboardKeySelector TargetKey;

};
