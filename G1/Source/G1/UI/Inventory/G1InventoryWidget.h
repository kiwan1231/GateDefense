// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/G1UserWidget.h"
#include "Item/G1ItemDefine.h"

#include "G1InventoryWidget.generated.h"

/**
 * 
 */
UCLASS()
class G1_API UG1InventoryWidget : public UG1UserWidget
{
	GENERATED_BODY()
	
public:
	UG1InventoryWidget();

protected:
	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
	TObjectPtr<class UG1InventorySlotsWidget> SlotsWidget;

	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
	TObjectPtr<class UG1EquipSlotWidget> WeaponSlotWidget;

	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
	TObjectPtr<class UG1EquipSlotWidget> ShieldSlotWidget;

	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
	TObjectPtr<class UG1EquipEntryWidget> WeaponEntryWidget;

	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
	TObjectPtr<class UG1EquipEntryWidget> ShieldEntryWidget;

	TMap<EEquipmentType, TObjectPtr<class UG1EquipEntryWidget>> EquipEntryMap;

private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UCanvasPanel> CanvasPanel_Equipment;

protected:
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<class AG1Player> G1Player;

private:
	bool IsInit = false;

public:
	void OnInitInventory(class AG1Player* Player);
	void OnRefreshInventory();

public:
	void Delegate_OnAddEquipment(class AG1Character* Character, FName ItemID);
	void Delegate_OnRemoveEquipment(class AG1Character* Character, EEquipmentType EquipType);

private:

};
