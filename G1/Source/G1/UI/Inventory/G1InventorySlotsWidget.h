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
class UG1EquipEntryWidget;
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
	UPROPERTY(BlueprintReadWrite)
	TSubclassOf<UG1InventorySlotWidget> SlotWidgetClass;

	UPROPERTY()
	TArray<TObjectPtr<UG1InventorySlotWidget>> SlotWidgets;

	UPROPERTY(BlueprintReadWrite)
	TSubclassOf<UG1InventoryEntryWidget> EntryWidgetClass;

	UPROPERTY()
	TArray<TObjectPtr<UG1InventoryEntryWidget>> EntryWidgets;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UUniformGridPanel> GridPanel_Slots;

protected:
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<class AG1Player> G1Player;

private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCanvasPanel> CanvasPanel_Entries;

public:
	void InitInventorySlots(class AG1Player* Player);
	bool IsDrag();
	void OnEquiptSlotItem(TObjectPtr<UG1InventoryEntryWidget> SlotEntry);
	void OnUnEquiptSlotItem(TObjectPtr<UG1EquipEntryWidget> SlotEntry);

public:
	void Delegate_OnCreateInventoryItem(class AG1Player* Player, FIntPoint ItemSlotPos);
	void Delegate_OnRemoveInventoryItem(class AG1Player* Player, FIntPoint ItemSlotPos);
	void Delegate_OnInventoryItemCount(class AG1Player*, FIntPoint ItemSlotPos, int32 ItemCount);

private:
	FIntPoint InventorySize = FIntPoint::ZeroValue;
	FIntPoint PrevDragOverSlotPos = FIntPoint::ZeroValue;
};
