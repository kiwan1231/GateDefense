// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Inventory/G1InventoryEntryWidget.h"
#include "Components/Image.h"
#include "Components/SizeBox.h"
#include "Components/TextBlock.h"
#include "UI/Inventory/G1InventorySlotWidget.h"
#include "UI/Inventory/G1InventorySlotsWidget.h"
#include "Item/G1Item2DInstance.h"
#include "UI/Item/Drag/G1DragDropOperation.h"
#include "UI/Item/Drag/G1ItemDragWidget.h"

UG1InventoryEntryWidget::UG1InventoryEntryWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}

void UG1InventoryEntryWidget::Init(UG1InventorySlotsWidget* InSlotsWidget, UG1Item2DInstance* InItemInstance, int32 InItemCount)
{
	SlotsWidget = InSlotsWidget;
	ItemInstance = InItemInstance;
	ItemCount = InItemCount;

	UTexture2D* Texture = InItemInstance->IconImage.LoadSynchronous();
	Image_Icon->SetBrushFromTexture(Texture);
}

void UG1InventoryEntryWidget::NativeConstruct()
{
	Super::NativeConstruct();

	Text_Count->SetText(FText::GetEmpty());
}

void UG1InventoryEntryWidget::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseEnter(InGeometry, InMouseEvent);

	Image_Hover->SetRenderOpacity(1.f);
}

void UG1InventoryEntryWidget::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseLeave(InMouseEvent);

	Image_Hover->SetRenderOpacity(0.f);
}

FReply UG1InventoryEntryWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FReply Replay = Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

	/// 드래그 체크
	if (InMouseEvent.GetEffectingButton() == EKeys::LeftMouseButton)
	{
		Replay.DetectDrag(TakeWidget(), EKeys::LeftMouseButton);
	}

	const FIntPoint UnitInventorySlotSize = FIntPoint(50, 50);

	FVector2D MouseWidgetPos = SlotsWidget->GetCachedGeometry().AbsoluteToLocal(InMouseEvent.GetScreenSpacePosition());
	FVector2D ItemWidgetPos = SlotsWidget->GetCachedGeometry().AbsoluteToLocal(InGeometry.LocalToAbsolute(UnitInventorySlotSize / 2.f));
	FIntPoint ItemSlotPos = FIntPoint(ItemWidgetPos.X / UnitInventorySlotSize.X, ItemWidgetPos.Y / UnitInventorySlotSize.Y);

	CachedFromSlotPos = ItemSlotPos;
	CachedDeltaWidgetPos = MouseWidgetPos - ItemWidgetPos;

	return Replay;
}

void UG1InventoryEntryWidget::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);

	if (DragWidgetClass == nullptr)
	{
		UE_LOG(LogTemp, Log, TEXT("DragWidgetClass IS NULL"));
		return;
	}

	UG1ItemDragWidget* DragWidget = CreateWidget<UG1ItemDragWidget>(GetOwningPlayer(), DragWidgetClass);
	FVector2D EntityWidgetSize = FVector2D(1 * 50, 1 * 50);
	DragWidget->Init(EntityWidgetSize, nullptr, ItemCount);

	UG1DragDropOperation* DragDrop = NewObject<UG1DragDropOperation>();
	DragDrop->DefaultDragVisual = DragWidget;
	DragDrop->Pivot = EDragPivot::MouseDown;
	DragDrop->FromItemSlotPos = CachedFromSlotPos;
	DragDrop->ItemInstance = ItemInstance;
	DragDrop->DeltaWidgetPos = CachedDeltaWidgetPos;

	OutOperation = DragDrop;
}

void UG1InventoryEntryWidget::NativeOnDragCancelled(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDragCancelled(InDragDropEvent, InOperation);

	RefreshWidgetOpacity(true);
}

void UG1InventoryEntryWidget::RefreshWidgetOpacity(bool bClearlyVisible)
{
	SetRenderOpacity(bClearlyVisible ? 1.f : 0.5f);
}

void UG1InventoryEntryWidget::RefreshItemCount(int32 NewItemCount)
{
	ItemCount = NewItemCount;
	Text_Count->SetText((ItemCount >= 2) ? FText::AsNumber(ItemCount) : FText::GetEmpty());
}