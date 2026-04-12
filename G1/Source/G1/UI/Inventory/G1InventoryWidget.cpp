// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Inventory/G1InventoryWidget.h"

#include "Character/G1Player.h"

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
	/*
	auto Items = G1Player->GetItems();
	for (int i = 0; i < Items.Num(); i++)
	{
		if (Items[i].ItemID == FName::IsNone)
		{
			if (Items[i].Count > Count)
			{
				Items[i].Count -= Count;
			}
			else
			{
				Items[i].ItemID = NAME_None;
				Items[i].IsStackable = false;
				Items[i].Count = 0;
			}
			break;
		}
	}
	*/
}
