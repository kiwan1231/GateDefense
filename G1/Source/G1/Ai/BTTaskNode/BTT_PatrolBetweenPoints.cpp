#include "Ai/BTTaskNode/BTT_PatrolBetweenPoints.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "GameFramework/Character.h"

UBTT_PatrolBetweenPoints::UBTT_PatrolBetweenPoints()
{
	NodeName = TEXT("Patrol Between Points");
	bNotifyTick = true;
}

EBTNodeResult::Type UBTT_PatrolBetweenPoints::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBlackboardComponent* BB = OwnerComp.GetBlackboardComponent();
	if (!BB) return EBTNodeResult::Failed;

	PatrolA = BB->GetValueAsVector(TEXT("PatrolPosA"));
	PatrolB = BB->GetValueAsVector(TEXT("PatrolPosB"));
	CurrentTarget = BB->GetValueAsVector(TEXT("CurrentPatrolTarget"));

	AAIController* AIController = OwnerComp.GetAIOwner();
	if (!AIController) return EBTNodeResult::Failed;

	// 목표 위치까지 이동 시작
	AIController->MoveToLocation(CurrentTarget, 5.0f);
	bWaiting = false;
	ElapsedTime = 0.0f;

	return EBTNodeResult::InProgress;
}

void UBTT_PatrolBetweenPoints::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	AAIController* AIController = OwnerComp.GetAIOwner();
	APawn* Pawn = AIController ? AIController->GetPawn() : nullptr;
	if (!Pawn) return;

	const float Distance = FVector::Dist(Pawn->GetActorLocation(), CurrentTarget);

	if (!bWaiting && Distance < 100.0f) // 도착 판정
	{
		bWaiting = true;
		ElapsedTime = 0.0f;

		// 다음 목표 위치 계산
		FVector NextTarget = (CurrentTarget.Equals(PatrolA, 1.0f)) ? PatrolB : PatrolA;
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(TEXT("CurrentPatrolTarget"), NextTarget);

		// 회전 처리
		FRotator LookAtRot = (NextTarget - Pawn->GetActorLocation()).Rotation();
		Pawn->SetActorRotation(LookAtRot);
	}

	if (bWaiting)
	{
		ElapsedTime += DeltaSeconds;
		if (ElapsedTime >= WaitTime)
		{
			// 대기 끝, 이동 재시작
			CurrentTarget = OwnerComp.GetBlackboardComponent()->GetValueAsVector(TEXT("CurrentPatrolTarget"));
			AIController->MoveToLocation(CurrentTarget, 5.0f);
			bWaiting = false;
		}
	}
}

void UBTT_PatrolBetweenPoints::OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTNodeResult::Type TaskResult)
{
	bWaiting = false;
	ElapsedTime = 0.0f;
}
