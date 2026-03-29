// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/G1UserWidget.h"
#include "G1GameOverSceneWidget.generated.h"

/**
 * 
 */
UCLASS()
class G1_API UG1GameOverSceneWidget : public UG1UserWidget
{
	GENERATED_BODY()
	
public:
	UG1GameOverSceneWidget(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	virtual FReply NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;

protected:
	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
	TObjectPtr<class UTextBlock> Presskey;

protected:
	UPROPERTY(BlueprintReadOnly)
	float ElapsedTime = 0.f;
	UPROPERTY(BlueprintReadOnly)
	bool EnableRestart = false;
};
