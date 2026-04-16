// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/G1UserWidget.h"
#include "G1EquipSlotWidget.generated.h"

class UImage;
class USizeBox;

/**
 * 
 */
UCLASS()
class G1_API UG1EquipSlotWidget : public UG1UserWidget
{
	GENERATED_BODY()
	
public:
	UG1EquipSlotWidget(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:
	virtual void NativeConstruct() override;

public:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<USizeBox> SizeBox_Root;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> Image_Slot;
};
