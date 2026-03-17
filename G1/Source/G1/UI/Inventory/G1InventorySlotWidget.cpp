// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Inventory/G1InventorySlotWidget.h"
#include "Components/SizeBox.h"

UG1InventorySlotWidget::UG1InventorySlotWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UG1InventorySlotWidget::NativeConstruct()
{
	Super::NativeConstruct();

	SizeBox_Root->SetWidthOverride(50);
	SizeBox_Root->SetHeightOverride(50);
}
