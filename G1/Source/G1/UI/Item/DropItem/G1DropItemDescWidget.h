// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/G1UserWidget.h"
#include "G1DropItemDescWidget.generated.h"

/**
 * 
 */
UCLASS()
class G1_API UG1DropItemDescWidget : public UG1UserWidget
{
	GENERATED_BODY()
public:
	UG1DropItemDescWidget(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	virtual void NativeConstruct() override;

public:
	void SetItem(const FName ItemID);
	void Show();
	void Hide();
	void UpdatePosition(const FVector& WorldLocation);

protected:
	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
	TObjectPtr<class UTextBlock> ItemName;
	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
	TObjectPtr<class UTextBlock> ItemType;
	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
	TObjectPtr<class UTextBlock> ItemDesc;
	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
	TObjectPtr<class UTextBlock> ItemAttribute;

protected:
	UPROPERTY(BlueprintReadOnly)
	FName CurrentItemID;
};
