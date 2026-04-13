// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Inventory/G1InventoryWidget.h"
#include "UI/Inventory/G1InventorySlotsWidget.h"

#include "Character/G1Player.h"
#include "Player/G1PlayerInventory.h"

UG1InventoryWidget::UG1InventoryWidget()
	: Super()
{
}

void UG1InventoryWidget::OnInitInventory(AG1Player* Player)
{
	G1Player = Player;

	IsInit = true;

	OnRefreshInventory();
}

void UG1InventoryWidget::OnRefreshInventory()
{
	if (IsInit == false)
	{
		return;
	}
	
	if (SlotsWidget == nullptr)
	{
		return;
	}

	SlotsWidget->InitInventorySlots(G1Player);
}
