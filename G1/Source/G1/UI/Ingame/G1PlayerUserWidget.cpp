// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Ingame/G1PlayerUserWidget.h"
#include "G1PlayerUserWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

UG1PlayerUserWidget::UG1PlayerUserWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UG1PlayerUserWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UG1PlayerUserWidget::SetName(const FString& Name)
{
	if (PlayerName != nullptr)
	{
		PlayerName->SetText(FText::FromString(Name));
	}
}

void UG1PlayerUserWidget::SetHpRatio(float Ratio)
{
	if (HpBar != nullptr)
	{
		HpBar->SetPercent(Ratio);
	}
}
