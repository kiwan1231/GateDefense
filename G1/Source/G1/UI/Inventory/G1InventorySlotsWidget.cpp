// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Inventory/G1InventorySlotsWidget.h"
#include "Components/UniformGridPanel.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "UI/Inventory/G1InventorySlotWidget.h"
#include "G1InventoryEntryWidget.h"
#include "Subsystems/SubsystemBlueprintLibrary.h"
#include "Item/G1InventorySubsystem.h"
#include "UI/Item/Drag/G1DragDropOperation.h"
#include "Item/G1Item2DInstance.h"

#include "Item/G1ItemDefine.h"

#include "Character/G1Player.h"
#include "Player/G1PlayerInventory.h"

UG1InventorySlotsWidget::UG1InventorySlotsWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	/*ConstructorHelpers::FClassFinder<UG1InventorySlotWidget> FindSlotWidgetClass(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/UI/Item/Inventory/WBP_InventorySlot.WBP_InventorySlot_C'"));

	if (FindSlotWidgetClass.Succeeded())
	{
		SlotWidgetClass = FindSlotWidgetClass.Class;
	}

	ConstructorHelpers::FClassFinder<UG1InventoryEntryWidget> FindEntryWidgetClass(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/UI/Item/Inventory/WBP_InventoryEntry.WBP_InventoryEntry_C'"));

	if (FindEntryWidgetClass.Succeeded())
	{
		EntryWidgetClass = FindEntryWidgetClass.Class;
	}*/
}

void UG1InventorySlotsWidget::NativeConstruct()
{
	Super::NativeConstruct();

	/*for (int32 y = 0; y < Y_COUNT; y++)
	{
		for (int32 x = 0; x < X_COUNT; x++)
		{
			int index = y * X_COUNT + x;

			UR1InventorySlotWidget* SlotWidget = CreateWidget<UR1InventorySlotWidget>(GetOwningPlayer(), SlotWidgetClass);
			EntryWidgets[index] = SlotWidget;
			GridPanel_Slots->AddChildToUniformGrid(SlotWidget, y, x);
		}
	}*/
}

void UG1InventorySlotsWidget::OnInventoryEntryChanged(const FIntPoint& ItemSlotPos, TObjectPtr<UG1Item2DInstance> Item)
{
	int32 SlotIndex = ItemSlotPos.Y * X_COUNT + ItemSlotPos.X;

	if (UG1InventoryEntryWidget* EntryWidget = EntryWidgets[SlotIndex])
	{
		if (Item == nullptr)
		{
			CanvasPanel_Entries->RemoveChild(EntryWidget);
			EntryWidgets[SlotIndex] = nullptr;
		}
	}
	else
	{
		EntryWidget = CreateWidget<UG1InventoryEntryWidget>(GetOwningPlayer(), EntryWidgetClass);
		EntryWidgets[SlotIndex] = EntryWidget;

		UCanvasPanelSlot* CanvasPanelSlot = CanvasPanel_Entries->AddChildToCanvas(EntryWidget);
		CanvasPanelSlot->SetAutoSize(true);
		CanvasPanelSlot->SetPosition(FVector2D(ItemSlotPos.X * 50, ItemSlotPos.Y * 50));

		EntryWidget->Init(this, Item, 1);
	}
}

bool UG1InventorySlotsWidget::NativeOnDragOver(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDragOver(InGeometry, InDragDropEvent, InOperation);

	UG1DragDropOperation* DragDrop = Cast<UG1DragDropOperation>(InOperation);
	check(DragDrop);

	FVector2D MouseWidgetPos = InGeometry.AbsoluteToLocal(InDragDropEvent.GetScreenSpacePosition());
	FVector2D ToWidgetPos = MouseWidgetPos - DragDrop->DeltaWidgetPos;
	FIntPoint ToSlotPos = FIntPoint(ToWidgetPos.X / InventoryItem::UnitInventorySlotSize.X, ToWidgetPos.Y / InventoryItem::UnitInventorySlotSize.Y);

	if (PrevDragOverSlotPos == ToSlotPos)
		return true;

	PrevDragOverSlotPos = ToSlotPos;

	// TODO

	return false;
}

void UG1InventorySlotsWidget::NativeOnDragLeave(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDragLeave(InDragDropEvent, InOperation);
	FinishDrag();
}

bool UG1InventorySlotsWidget::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);
	FinishDrag();

	UG1DragDropOperation* DragDrop = Cast<UG1DragDropOperation>(InOperation);
	check(DragDrop);

	FVector2D MouseWidgetPos = InGeometry.AbsoluteToLocal(InDragDropEvent.GetScreenSpacePosition());
	FVector2D ToWidgetPos = MouseWidgetPos - DragDrop->DeltaWidgetPos;
	FIntPoint ToItemSlotPos = FIntPoint(ToWidgetPos.X / InventoryItem::UnitInventorySlotSize.X, ToWidgetPos.Y / InventoryItem::UnitInventorySlotSize.Y);

	// TODO
	if (DragDrop->FromItemSlotPos != ToItemSlotPos)
	{
		OnInventoryEntryChanged(DragDrop->FromItemSlotPos, nullptr);
		OnInventoryEntryChanged(ToItemSlotPos, DragDrop->ItemInstance);
	}

	return false;
}

void UG1InventorySlotsWidget::FinishDrag()
{
	PrevDragOverSlotPos = FIntPoint(-1, -1);
}

void UG1InventorySlotsWidget::InitInventorySlots(AG1Player* Player)
{
	G1Player = Player;

	auto InventoryComponent = G1Player->GetInventoryComponent();
	auto InventorySize = InventoryComponent->GetInventorySize();
	auto InventoryItems = InventoryComponent->GetInventoryItems();

	InventoryComponent->OnCreateInventoryItem.AddUObject(this, &UG1InventorySlotsWidget::Delegate_OnCreateInventoryItem);
	InventoryComponent->OnRemoveInventoryItem.AddUObject(this, &UG1InventorySlotsWidget::Delegate_OnRemoveInventoryItem);
	InventoryComponent->OnInventoryItemCount.AddUObject(this, &UG1InventorySlotsWidget::Delegate_OnInventoryItemCount);

	SlotWidgets.SetNum(InventoryItems.Num());
	for (int i = 0; i < InventoryItems.Num(); i++)
	{
		UG1InventorySlotWidget* SlotWidget = CreateWidget<UG1InventorySlotWidget>(GetOwningPlayer(), SlotWidgetClass);
		SlotWidgets[i] = SlotWidget;
		GridPanel_Slots->AddChildToUniformGrid(SlotWidget, i / X_COUNT, i % X_COUNT);
	}

	EntryWidgets.SetNum(InventoryItems.Num());
	for (int i = 0; i < InventoryItems.Num(); i++)
	{
		if (InventoryItems[i] != nullptr)
		{
			FIntPoint ItemSlotPos = FIntPoint(i % X_COUNT, i / X_COUNT);
			OnInventoryEntryChanged(InventoryItems[i]->InventorySlotPos, InventoryItems[i]);
		}
	}
}

void UG1InventorySlotsWidget::Delegate_OnCreateInventoryItem(AG1Player* Player, FIntPoint ItemSlotPos)
{
	if (G1Player != Player)
		return;

	auto InventoryComponent = G1Player->GetInventoryComponent();
	auto InventoryItems = InventoryComponent->GetInventoryItems();

	for (int i = 0; i < InventoryItems.Num(); i++)
	{
		if (InventoryItems[i] != nullptr && InventoryItems[i]->InventorySlotPos == ItemSlotPos)
		{
			OnInventoryEntryChanged(InventoryItems[i]->InventorySlotPos, InventoryItems[i]);
		}
	}
}

void UG1InventorySlotsWidget::Delegate_OnRemoveInventoryItem(AG1Player* Player, FIntPoint ItemSlotPos)
{
	if (G1Player != Player)
		return;

	for (int i = 0; i < EntryWidgets.Num(); i++)
	{
		if (EntryWidgets[i] == nullptr)
			continue;

		if (EntryWidgets[i]->GetSlotPos() == ItemSlotPos)
		{
			EntryWidgets[i] = nullptr;
			break;
		}
	}
}

void UG1InventorySlotsWidget::Delegate_OnInventoryItemCount(AG1Player* Player, FIntPoint ItemSlotPos, int32 ItemCount)
{
}
