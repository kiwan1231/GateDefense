// Fill out your copyright notice in the Description page of Project Settings.


#include "BTD_CanAttack.h"
#include "AI/G1AIController.h"
#include "Character/G1Character.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTD_CanAttack::UBTD_CanAttack()
	: Super()
{
	NodeName = TEXT("CanAttack");
}

bool UBTD_CanAttack::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (ControllingPawn == nullptr)
	{
		return false;
	}

	AG1Character* Target = Cast<AG1Character>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(TargetKey.SelectedKeyName));
	if (Target == nullptr)
	{
		return false;
	}

	return (Target->EnableAbility() && Target->GetDistanceTo(ControllingPawn) <= AttackRange);
}
