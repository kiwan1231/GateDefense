// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/G1UserWidget.h"
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
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<class AG1Player> G1Player;

private:
	bool IsInit = false;

public:
	void OnInitInventory(class AG1Player* Player);
	void OnRefreshInventory();
};
