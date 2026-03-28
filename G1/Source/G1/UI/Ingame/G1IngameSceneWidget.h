// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/G1UserWidget.h"
#include "G1IngameSceneWidget.generated.h"

/**
 * 
 */
UCLASS()
class G1_API UG1IngameSceneWidget : public UG1UserWidget
{
	GENERATED_BODY()
	
public:
	UG1IngameSceneWidget(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

public:
	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
	TObjectPtr<class UG1PlayerUserWidget> PlayerWidget;
};
