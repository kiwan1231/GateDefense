// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/G1Monster.h"
#include "AbilitySystem/Attributes/G1MonsterSet.h"
#include "AbilitySystem/G1AbilitySystem.h"

AG1Monster::AG1Monster()
	: Super()
{
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.f, 0.f, -88.f), FRotator(0.f, -90.f, 0.f));

	AbilitySystem = CreateDefaultSubobject<UG1AbilitySystem>("AbilitySystem");

	AttributeSet = CreateDefaultSubobject<UG1MonsterSet>("MonsterSet");
}

void AG1Monster::BeginPlay()
{
	Super::BeginPlay();

	InitAbilitySystem();
}

void AG1Monster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AG1Monster::InitAbilitySystem()
{
	Super::InitAbilitySystem();

	AbilitySystem->InitAbilityActorInfo(this, this);
}
