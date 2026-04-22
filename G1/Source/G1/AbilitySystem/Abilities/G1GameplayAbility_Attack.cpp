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
				FName CurrentSection = AnimInstance->Montage_GetCurrentSection(AttackMontage);

				for (const FG1MontageSectionData& Data : AttackMontageSectionDatas)
				{
					if (Data.CurSectionName == CurrentSection)
					{
						if (Data.NextSectionName == NAME_None)
							continue;

						switch (Data.NextPlayType)
						{
						case EAbilityMontagePlayType::Normal:
							Player->PlayAnimMontage(AttackMontage, 1.0f, Data.NextSectionName);
							break;

						case EAbilityMontagePlayType::JumpToSection:
							AnimInstance->Montage_JumpToSection(Data.NextSectionName, AttackMontage);
							break;

						case EAbilityMontagePlayType::SetNextSection:
							AnimInstance->Montage_SetNextSection(Data.CurSectionName, Data.NextSectionName, AttackMontage);
							break;
						}

						break;
					}
				}
			}
			else
			{
				// 첫 섹션 자동 시작 (배열 기준)
				if (AttackMontageSectionDatas.Num() > 0)
				{
					Player->PlayAnimMontage(AttackMontage,1.0f,AttackMontageSectionDatas[0].CurSectionName);
				}
				else
				{
					Player->PlayAnimMontage(AttackMontage);
				}
			}
		}
	}
}

void UG1GameplayAbility_Attack::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}
