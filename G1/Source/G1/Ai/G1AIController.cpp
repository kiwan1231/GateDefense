// Fill out your copyright notice in the Description page of Project Settings.


#include "Ai/G1AIController.h"
#include "Navigation/PathFollowingComponent.h"

AG1AIController::AG1AIController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void AG1AIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
}

void AG1AIController::BeginPlay()
{
	Super::BeginPlay();

	FVector Dest = { 0,0,0 };

	FAIMoveRequest MoveRequest;
	MoveRequest.SetGoalLocation(Dest);
	MoveRequest.SetAcceptanceRadius(15.f);

	FNavPathSharedPtr NavPath;
	MoveTo(MoveRequest, OUT & NavPath);

	/*if (NavPath.IsValid())
	{
		TArray<FNavPathPoint>& PathPoints = NavPath->GetPathPoints();
		for (const auto& Point : PathPoints)
		{
			const FVector& Location = Point.Location;
			DrawDebugSphere(GetWorld(), Location, 12.f, 12, FColor::Green, false, 10.0f);
		}
	}*/
}

void AG1AIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
