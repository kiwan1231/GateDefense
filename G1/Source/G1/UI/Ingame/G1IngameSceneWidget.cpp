// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Ingame/G1IngameSceneWidget.h"
#include "G1IngameSceneWidget.h"

#include "UI/Inventory/G1InventoryWidget.h"

UG1IngameSceneWidget::UG1IngameSceneWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UG1IngameSceneWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (PlayerInventory != nullptr && PlayerInventory->IsValidLowLevel())
	{
		PlayerInventory->Hide();
	}
}

void UG1IngameSceneWidget::OnInputInventory()
{
	if (PlayerInventory != nullptr && PlayerInventory->IsValidLowLevel())
	{
		if (PlayerInventory->IsVisible())
		{
			PlayerInventory->Hide();
		}
		else
		{
			PlayerInventory->Show();
		}
	}
}
