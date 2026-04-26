// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/G1AnimNotifySend.h"
#include "Character/G1Character.h"
#include "Animation/AnimMontage.h"

UG1AnimNotifySend::UG1AnimNotifySend(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UG1AnimNotifySend::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

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

	AG1Character* Character = Cast<AG1Character>(Owner);
	if (!Character)
	{
		return;
	}

	// Animation이 Montage일 때만 처리
	UAnimMontage* Montage = Cast<UAnimMontage>(Animation);
	if (Montage)
	{
		Character->HandleGameplayEvent(Montage, EventTag, EventType);
	}
}
