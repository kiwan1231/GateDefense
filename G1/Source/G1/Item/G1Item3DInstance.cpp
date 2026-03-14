// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/G1Item3DInstance.h"

// Sets default values
AG1Item3DInstance::AG1Item3DInstance()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AG1Item3DInstance::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AG1Item3DInstance::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

