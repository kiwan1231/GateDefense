// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/G1UserWidget.h"
#include "G1InventoryEntryWidget.generated.h"

class UImage;
class USizeBox;
class UTextBlock;
class UG1InventorySlotsWidget;
class UG1Item2DInstance;
class UG1ItemDragWidget;

/**
 * 
 */
UCLASS()
class G1_API UG1InventoryEntryWidget : public UG1UserWidget
{
	GENERATED_BODY()
	
public:
	UG1InventoryEntryWidget(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

public:
	void Init(UG1InventorySlotsWidget* InSlotsWidget, UG1Item2DInstance* InItemInstance, int32 InItemCount);

	void UpdateItemCount(int32 NewItemCount);

protected:
	virtual void NativeConstruct() override;
	virtual void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent)override;
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;
	virtual void NativeOnDragCancelled(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;

	void RefreshWidgetOpacity(bool bClearlyVisible);
	void RefreshItemCount(int32 NewItemCount);

private:
	FIntPoint  CachedFromSlotPos = FIntPoint::ZeroValue;
	FVector2D  CachedDeltaWidgetPos = FVector2D::ZeroVector;
	int32 ItemCount = 0;

protected:
	UPROPERTY()
	TObjectPtr<UG1InventorySlotsWidget> SlotsWidget;

	UPROPERTY()
	TObjectPtr<UG1Item2DInstance> ItemInstance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)

	TSubclassOf<UG1ItemDragWidget> DragWidgetClass;
protected:

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<USizeBox> SizeBox_Root;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> Text_Count;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> Image_Icon;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> Image_Hover;

public:
	FIntPoint GetSlotPos();
};
