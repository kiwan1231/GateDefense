// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/G1AnimNotifyState.h"
#include "Character/G1Character.h"

UG1AnimNotifyState::UG1AnimNotifyState(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UG1AnimNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

	// 안전한 널 체크: MeshComp가 유효하지 않으면 더 이상 진행하지 않음
	if (!MeshComp)
	{
		return;
	}

	AActor* Owner = MeshComp->GetOwner();
	if (!Owner)
	{
		return;
	}

	AG1Character* OwnerCharacter = Cast<AG1Character>(Owner);
	if (!OwnerCharacter)
	{
		return;
	}

	// Animation이 Montage일 때만 처리
	UAnimMontage* Montage = Cast<UAnimMontage>(Animation);
	if (Montage)
	{
		OwnerCharacter->HandleEventAnimNotifyStateBegin(Montage, EventTag);
	}
}

void UG1AnimNotifyState::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, FrameDeltaTime, EventReference);
}

void UG1AnimNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);

	// 안전한 널 체크: MeshComp가 유효하지 않으면 더 이상 진행하지 않음
	if (!MeshComp)
	{
		return;
	}

	AActor* Owner = MeshComp->GetOwner();
	if (!Owner)
	{
		return;
	}

	AG1Character* OwnerCharacter = Cast<AG1Character>(Owner);
	if (!OwnerCharacter)
	{
		return;
	}

	// Animation이 Montage일 때만 처리
	UAnimMontage* Montage = Cast<UAnimMontage>(Animation);
	if (Montage)
	{
		OwnerCharacter->HandleEventAnimNotifyStateEnd(Montage, EventTag);
	}
}
