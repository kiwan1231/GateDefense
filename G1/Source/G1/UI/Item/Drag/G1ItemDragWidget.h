// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/G1UserWidget.h"
#include "G1ItemDragWidget.generated.h"

class UImage;
class USizeBox;
class UTextBlock;
class UTexture2D;
class UG1InventorySlotsWidget;

/**
 * 
 */
UCLASS()
class G1_API UG1ItemDragWidget : public UG1UserWidget
{
	GENERATED_BODY()
	
public:
	UG1ItemDragWidget(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

public:
	void Init(const FVector2D& InWidgetSize, UTexture2D* InItemIcon, int32 InItemCount);

protected:

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<USizeBox> SizeBox_Root;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> Text_Count;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> Image_Icon;
};
