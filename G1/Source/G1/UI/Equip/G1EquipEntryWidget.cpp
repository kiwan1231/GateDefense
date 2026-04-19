// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Equip/G1EquipEntryWidget.h"

#include "Data/G1ItemData.h"

#include "Components/Image.h"

#include "Item/G1Item2DInstance.h"

UG1EquipEntryWidget::UG1EquipEntryWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	ItemInstance = nullptr;
	EquipType = EEquipmentType::None;
}

void UG1EquipEntryWidget::Init(UG1Item2DInstance* _InItemInstance, EEquipmentType _Type)
{
	ItemInstance = _InItemInstance;

	UTexture2D* Texture = nullptr;

	if (_InItemInstance->IconImage.IsNull() == false)
	{
		Texture = _InItemInstance->IconImage.LoadSynchronous();
	}

	Image_Icon->SetBrushFromTexture(Texture);
}

void UG1EquipEntryWidget::SetItemInstance(EItemSlotType _ItemSlotType, int32 _X, int32 _Y, FName _ItemID, int32 _Count, const UG1ItemData* _ItemData)
{
	if (ItemInstance != nullptr)
	{
		ItemInstance->Init(_ItemSlotType, _X, _Y, _ItemID, _Count, _ItemData);

		UTexture2D* Texture = nullptr;

		if (ItemInstance->IconImage.IsNull() == false)
		{
			Texture = ItemInstance->IconImage.LoadSynchronous();
		}

		Image_Icon->SetBrushFromTexture(Texture);
	}
}

void UG1EquipEntryWidget::NativeConstruct()
{
}

FReply UG1EquipEntryWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FReply Replay = Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

	return Replay;
}
