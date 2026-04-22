// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "G1GameplayAbility.generated.h"

UENUM(BlueprintType)
enum class EAbilityMontagePlayType : uint8
{
	Normal,
	JumpToSection,
	SetNextSection
};

USTRUCT(BlueprintType)
struct FG1MontageSectionData
{
	GENERATED_BODY()

public:

	// 몽타주 섹션 이름
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName CurSectionName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName NextSectionName;

	// 실행 타입
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EAbilityMontagePlayType NextPlayType = EAbilityMontagePlayType::Normal;
};

/**
 * 
 */
UCLASS()
class G1_API UG1GameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

};
