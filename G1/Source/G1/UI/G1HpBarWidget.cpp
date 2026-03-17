// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/G1HpBarWidget.h"
#include "Components/ProgressBar.h"
UG1HpBarWidget::UG1HpBarWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UG1HpBarWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UG1HpBarWidget::SetHpRatio(float Ratio)
{
	if (HpBar)
	{
		HpBar->SetPercent(Ratio);
	}
}
