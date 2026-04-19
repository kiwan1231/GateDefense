// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/G1UserWidget.h"
#include "Item/G1ItemDefine.h"


#include "G1EquipEntryWidget.generated.h"

class UImage;
class USizeBox;
class UTextBlock;
class UG1InventorySlotsWidget;
class UG1Item2DInstance;
class UG1ItemDragWidget;
class UG1ItemData;
/**
 * 
 */
UCLASS()
class G1_API UG1EquipEntryWidget : public UG1UserWidget
{
	GENERATED_BODY()
	
public:
	UG1EquipEntryWidget(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

public:
	void Init(UG1Item2DInstance* _InItemInstance, EEquipmentType _Type);
	void SetItemInstance(EItemSlotType _ItemSlotType, int32 _X, int32 _Y, FName _ItemID, int32 _Count, const UG1ItemData* _ItemData);
protected:
	virtual void NativeConstruct() override;
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

protected:
	UPROPERTY()
	TObjectPtr<UG1Item2DInstance> ItemInstance;
	UPROPERTY()
	EEquipmentType EquipType;

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> Image_Icon;

public:
	TObjectPtr<UG1Item2DInstance> GetItemInstance() const { return ItemInstance; }
	EEquipmentType GetEquipType() const { return EquipType; }
};
