// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Equip/G1EquipEntryWidget.h"

#include "UI/Inventory/G1InventorySlotsWidget.h"

#include "Data/G1ItemData.h"

#include "Components/Image.h"

#include "Item/G1Item2DInstance.h"

UG1EquipEntryWidget::UG1EquipEntryWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	ItemInstance = nullptr;
	EquipType = EEquipmentType::None;
}

void UG1EquipEntryWidget::Init(UG1InventorySlotsWidget* InSlotsWidget, UG1Item2DInstance* _InItemInstance, EEquipmentType _Type)
{
	SlotsWidget = InSlotsWidget;

	ItemInstance = _InItemInstance;

	EquipType = _Type;

	UpdateIconByItemInstance();
}

void UG1EquipEntryWidget::SetItemInstance(EItemSlotType _ItemSlotType, int32 _X, int32 _Y, FName _ItemID, int32 _Count, const UG1ItemData* _ItemData)
{
	if (ItemInstance != nullptr)
	{
		ItemInstance->Init(_ItemSlotType, _X, _Y, _ItemID, _Count, _ItemData);

		UpdateIconByItemInstance();
	}
}

void UG1EquipEntryWidget::NativeConstruct()
{
	UpdateIconByItemInstance();
}

FReply UG1EquipEntryWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FReply Replay = Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

	if (InMouseEvent.GetEffectingButton() == EKeys::RightMouseButton)
	{
		SlotsWidget->OnUnEquiptSlotItem(this);

		return Replay;
	}

	return Replay;
}

void UG1EquipEntryWidget::RefreshWidgetOpacity(bool bClearlyVisible)
{
	SetRenderOpacity(bClearlyVisible ? 1.f : 0.5f);
}

void UG1EquipEntryWidget::UpdateIconByItemInstance()
{
	if (ItemInstance != nullptr && ItemInstance->IconImage .IsNull() == false)
	{
		UTexture2D* Texture = ItemInstance->IconImage.LoadSynchronous();
		Image_Icon->SetBrushFromTexture(Texture);
		RefreshWidgetOpacity(true);
	}
	else
	{
		RefreshWidgetOpacity(false);
	}
}
