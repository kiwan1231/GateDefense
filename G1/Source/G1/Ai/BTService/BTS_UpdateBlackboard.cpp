// Fill out your copyright notice in the Description page of Project Settings.


#include "Ai/BTService/BTS_UpdateBlackboard.h"
#include "AI/G1AIController.h"
#include "Character/G1Character.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTS_UpdateBlackboard::UBTS_UpdateBlackboard()
	: Super()
{
	NodeName = TEXT("UpdateBlackboard");
	Interval = 0.5f;
}

void UBTS_UpdateBlackboard::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	APawn* LocalPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (LocalPawn == nullptr)
	{
		return;
	}

	AG1Character* G1Character = Cast<AG1Character>(LocalPawn);
	if (G1Character != nullptr)
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(DeadStateKey.SelectedKeyName, G1Character->InDeadState());
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(EnableMoveKey.SelectedKeyName, G1Character->EnableMove());
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(EnableAttackKey.SelectedKeyName, G1Character->EnableAbility());
	}
}
