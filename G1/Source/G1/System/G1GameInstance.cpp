// Fill out your copyright notice in the Description page of Project Settings.


#include "System/G1GameInstance.h"
#include "G1AssetManager.h"

UG1GameInstance::UG1GameInstance(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UG1GameInstance::Init()
{
	Super::Init();

	UG1AssetManager::Initialize();
}

void UG1GameInstance::Shutdown()
{
	Super::Shutdown();
}
