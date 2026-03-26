// Fill out your copyright notice in the Description page of Project Settings.


#include "Ai/BTDecorator/BTD_CheckBlackboardByBool.h"
#include "AI/G1AIController.h"
#include "Character/G1Character.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Bool.h"

UBTD_CheckBlackboardByBool::UBTD_CheckBlackboardByBool()
	: Super()
{
	NodeName = TEXT("CheckBlackboardByBool");
}

bool UBTD_CheckBlackboardByBool::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	return OwnerComp.GetBlackboardComponent()->GetValueAsBool(BoolValueKey.SelectedKeyName);
}
