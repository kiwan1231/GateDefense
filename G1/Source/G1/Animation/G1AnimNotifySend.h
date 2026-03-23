// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "GameplayTagContainer.h"
#include "Character/G1CharacterDefine.h"

#include "G1AnimNotifySend.generated.h"

/**
 * 
 */
UCLASS()
class G1_API UG1AnimNotifySend : public UAnimNotify
{
	GENERATED_BODY()
	
public:
	UG1AnimNotifySend(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;

protected:
	UPROPERTY(EditAnywhere)
	FGameplayTag EventTag;
	UPROPERTY(EditAnywhere)
	ECharacterAnimNotiType EventType;
};
