// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/G1UserWidget.h"

UG1UserWidget::UG1UserWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UG1UserWidget::Show()
{
	SetVisibility(ESlateVisibility::Visible);
}

void UG1UserWidget::Hide()
{
	SetVisibility(ESlateVisibility::Hidden);
}