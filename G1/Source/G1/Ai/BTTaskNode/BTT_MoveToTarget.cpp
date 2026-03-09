// Fill out your copyright notice in the Description page of Project Settings.


#include "Ai/BTTaskNode/BTT_MoveToTarget.h"
#include "AI/G1AIController.h"
#include "Character/G1Character.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "NavigationSystem.h"

UBTT_MoveToTarget::UBTT_MoveToTarget()
	: Super()
{
}

EBTNodeResult::Type UBTT_MoveToTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	AG1Character* Target = Cast<AG1Character>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(TargetKey.SelectedKeyName));
	if (Target == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	AAIController* AIController = OwnerComp.GetAIOwner();
	if (!AIController) return EBTNodeResult::Failed;

	AIController->MoveToActor(Target, MinDist);

	return EBTNodeResult::Succeeded;
}
