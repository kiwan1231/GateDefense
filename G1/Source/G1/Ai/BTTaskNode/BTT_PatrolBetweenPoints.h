#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTT_PatrolBetweenPoints.generated.h"

UCLASS()
class G1_API UBTT_PatrolBetweenPoints : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTT_PatrolBetweenPoints();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	virtual void OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTNodeResult::Type TaskResult) override;

	// Patrol points and state
	FVector PatrolA;
	FVector PatrolB;
	FVector CurrentTarget;

	bool bWaiting = false;
	float ElapsedTime = 0.0f;

	UPROPERTY(EditAnywhere, Category = "Patrol")
	float WaitTime = 2.0f;
};
