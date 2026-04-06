// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/G1UserWidget.h"
#include "G1DropItemNameWidget.generated.h"

/**
 * 
 */
UCLASS()
class G1_API UG1DropItemNameWidget : public UG1UserWidget
{
	GENERATED_BODY()
public:
	UG1DropItemNameWidget(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	virtual void NativeConstruct() override;

public:
	void SetItem(const FName ItemID);

protected:
	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
	TObjectPtr<class UTextBlock> ItemName;

protected:
	UPROPERTY(BlueprintReadOnly)
	FName CurrentItemID;
};
