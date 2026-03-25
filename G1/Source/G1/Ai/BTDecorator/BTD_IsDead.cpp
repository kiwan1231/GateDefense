// Fill out your copyright notice in the Description page of Project Settings.


#include "Ai/BTDecorator/BTD_IsDead.h"
#include "AI/G1AIController.h"
#include "Character/G1Character.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTD_IsDead::UBTD_IsDead()
	: Super()
{
	NodeName = TEXT("IsDead");
}

bool UBTD_IsDead::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (ControllingPawn == nullptr)
	{
		return false;
	}

	AG1Character* AiCharacter = Cast<AG1Character>(ControllingPawn);
	if (AiCharacter == nullptr)
	{
		return false;
	}
	return AiCharacter->State == ECharacterState::Dead;
}