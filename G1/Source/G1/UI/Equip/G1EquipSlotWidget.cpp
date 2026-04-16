// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Equip/G1EquipSlotWidget.h"
#include "Components/SizeBox.h"

UG1EquipSlotWidget::UG1EquipSlotWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UG1EquipSlotWidget::NativeConstruct()
{
	Super::NativeConstruct();

	SizeBox_Root->SetWidthOverride(50);
	SizeBox_Root->SetHeightOverride(50);
}
