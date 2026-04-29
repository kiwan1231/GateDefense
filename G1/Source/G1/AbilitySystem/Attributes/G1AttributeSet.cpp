// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Attributes/G1AttributeSet.h"

#include "GameplayEffectExtension.h"

UG1AttributeSet::UG1AttributeSet()
{
	InitHealth(100.f);
	InitMaxHealth(100.f);
	InitBaseDamage(10.f);
}

void UG1AttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

    if (Attribute == GetHealthAttribute())
    {
        UE_LOG(LogTemp, Warning, TEXT("[Pre] Health 변경 예정: %f"), GetHealth());
    }
    else if (Attribute == GetMaxHealthAttribute())
    {
        UE_LOG(LogTemp, Warning, TEXT("[Pre] MaxHealth 변경 예정: %f"), GetMaxHealth());
    }
    else if (Attribute == GetBaseDamageAttribute())
    {
        UE_LOG(LogTemp, Warning, TEXT("[Pre] BaseDamage 변경 예정 %f"), GetBaseDamage());
    }
}

void UG1AttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
    Super::PostGameplayEffectExecute(Data);

    const FGameplayAttribute& Attribute = Data.EvaluatedData.Attribute;

    // 어떤 Effect인지
    const UGameplayEffect* GE = Data.EffectSpec.Def;

    if (Attribute == GetHealthAttribute())
    {
        UE_LOG(LogTemp, Warning, TEXT("[Post] Health: %f"), GetHealth());
    }
    else if (Attribute == GetMaxHealthAttribute())
    {
        UE_LOG(LogTemp, Warning, TEXT("[Post] MaxHealth: %f"), GetMaxHealth());
    }
    else if (Attribute == GetBaseDamageAttribute())
    {
        UE_LOG(LogTemp, Warning, TEXT("[Post] BaseDamage: %f"), GetBaseDamage());
    }

    // 공통 로그 (중요)
    if (GE)
    {
        UE_LOG(LogTemp, Warning, TEXT("  Effect: %s"), *GE->GetName());
    }

    UE_LOG(LogTemp, Warning, TEXT("  Magnitude: %f"), Data.EvaluatedData.Magnitude);
}
