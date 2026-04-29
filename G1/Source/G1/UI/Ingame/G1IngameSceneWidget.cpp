// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Ingame/G1IngameSceneWidget.h"
#include "G1IngameSceneWidget.h"

#include "UI/Inventory/G1InventoryWidget.h"
#include "UI/G1QuitGameWidget.h"

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
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerInventory is not valid!"));
	}

	if (QuitGameWidget != nullptr && QuitGameWidget->IsValidLowLevel())
	{
		QuitGameWidget->Hide();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("QuitGameWidget is not valid!"));
	}
}

bool UG1IngameSceneWidget::IsVisibleWidget() const
{
	return QuitGameWidget->IsVisible() || PlayerInventory->IsVisible();
}

void UG1IngameSceneWidget::OnInputInventory()
{
	if (QuitGameWidget->IsVisible())
	{
		return;
	}

	if (PlayerInventory->IsVisible())
	{
		PlayerInventory->Hide();
	}
	else
	{
		PlayerInventory->Show();
	}
}

void UG1IngameSceneWidget::OnInputESC()
{
	if (QuitGameWidget->IsVisible())
	{
		QuitGameWidget->Hide();
	}
	else if (PlayerInventory->IsVisible())
	{
		PlayerInventory->Hide();
	}
	else
	{
		QuitGameWidget->Show();
	}
}
