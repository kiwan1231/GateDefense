// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/G1UserWidget.h"

#include "G1InventorySlotsWidget.generated.h"

class UG1InventorySlotWidget;
class UUniformGridPanel;
class UG1InventoryEntryWidget;
class UG1Item2DInstance;
class UCanvasPanel;

/**
 * 
 */
UCLASS()
class G1_API UG1InventorySlotsWidget : public UG1UserWidget
{
	GENERATED_BODY()
	
public:
	UG1InventorySlotsWidget(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:
	virtual void NativeConstruct() override;

	void OnInventoryEntryChanged(const FIntPoint& ItemSlotPos, TObjectPtr<UG1Item2DInstance> Item);

	virtual bool NativeOnDragOver(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	virtual void NativeOnDragLeave(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;

private:
	void FinishDrag();

protected:
	UPROPERTY()
	TSubclassOf<UG1InventorySlotWidget> SlotWidgetClass;

	UPROPERTY()
	TArray<TObjectPtr<UG1InventorySlotWidget>> SlotWidgets;

	UPROPERTY()
	TSubclassOf<UG1InventoryEntryWidget> EntryWidgetClass;

	UPROPERTY()
	TArray<TObjectPtr<UG1InventoryEntryWidget>> EntryWidgets;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UUniformGridPanel> GridPanel_Slots;

private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCanvasPanel> CanvasPanel_Entries;

private:
	FIntPoint PrevDragOverSlotPos = FIntPoint::ZeroValue;
	const int X_COUNT = 10;
	const int Y_COUNT = 5;
};
