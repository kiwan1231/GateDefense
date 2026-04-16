// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/G1UserWidget.h"
#include "G1EquipEntryWidget.generated.h"

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
class G1_API UG1EquipEntryWidget : public UG1UserWidget
{
	GENERATED_BODY()
	
public:
	UG1EquipEntryWidget(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

public:
	void Init(UG1Item2DInstance* InItemInstance);

protected:
	UPROPERTY()
	TObjectPtr<UG1Item2DInstance> ItemInstance;

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> Image_Icon;
};
