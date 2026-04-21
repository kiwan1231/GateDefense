// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/G1GameplayAbility_Attack.h"
#include "Character/G1Player.h"

#include "Animation/G1AnimInstance.h"

UG1GameplayAbility_Attack::UG1GameplayAbility_Attack(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

bool UG1GameplayAbility_Attack::CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, OUT FGameplayTagContainer* OptionalRelevantTags) const
{
	if (Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags) == false)
	{
		return false;
	}

	return true;
}

void UG1GameplayAbility_Attack::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	if (AttackMontage)
	{
		AG1Player* Player = Cast<AG1Player>(ActorInfo->AvatarActor);

		UG1AnimInstance* AnimInstance = nullptr;

		if (USkeletalMeshComponent* MeshComp = Player->GetMesh())
		{
			if (UAnimInstance* RawAnim = MeshComp->GetAnimInstance())
			{
				AnimInstance = Cast<UG1AnimInstance>(RawAnim);
			}
		}

		if (AnimInstance != nullptr)
		{
			if (AnimInstance->Montage_IsPlaying(AttackMontage))
			{
				if(AnimInstance->Montage_GetCurrentSection(AttackMontage) == "First")
				{
					AnimInstance->Montage_SetNextSection("First", "Second", AttackMontage);
					UE_LOG(LogTemp, Log, TEXT("Test Montage Second"));
				}
				else if (AnimInstance->Montage_GetCurrentSection(AttackMontage) == "Second")
				{
					AnimInstance->Montage_SetNextSection("Second", "Third", AttackMontage);//Montage_JumpToSection
					UE_LOG(LogTemp, Log, TEXT("Test Montage Third"));
				}
				else
				{

				}
			}
			else
			{
				Player->PlayAnimMontage(AttackMontage, 1.0f, "First");
				UE_LOG(LogTemp, Log, TEXT("Test Montage First"));
			}
		}

		//Player->PlayAnimMontage(AttackMontage);
	}
}

void UG1GameplayAbility_Attack::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}
