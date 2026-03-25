// Fill out your copyright notice in the Description page of Project Settings.


#include "Ai/BTService/BTS_UpdateBlackboard.h"

UBTS_UpdateBlackboard::UBTS_UpdateBlackboard()
	: Super()
{
}

void UBTS_UpdateBlackboard::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}
