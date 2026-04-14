// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/DragDropOperation.h"

#include "G1DragDropOperation.generated.h"

struct FG1InventoryItemData;

/**
 * 
 */
UCLASS()
class G1_API UG1DragDropOperation : public UDragDropOperation
{
	GENERATED_BODY()
	
public:
	UG1DragDropOperation(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

public:
	FIntPoint FromItemSlotPos = FIntPoint::ZeroValue;
public:
	UPROPERTY()
	TObjectPtr<class UG1Item2DInstance> ItemInstance;

	FVector2D DeltaWidgetPos = FVector2D::ZeroVector;
};
