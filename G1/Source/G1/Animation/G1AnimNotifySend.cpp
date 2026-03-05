// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/G1AnimNotifySend.h"
#include "Character/G1Character.h"

UG1AnimNotifySend::UG1AnimNotifySend(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UG1AnimNotifySend::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	AG1Character* LocalCharacter = Cast<AG1Character>(MeshComp->GetOwner());
	if (LocalCharacter)
	{
		LocalCharacter->HandleGameplayEvent(EventTag);
	}
}
