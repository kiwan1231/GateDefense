// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/G1UserWidget.h"
#include "G1PlayerUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class G1_API UG1PlayerUserWidget : public UG1UserWidget
{
	GENERATED_BODY()
	
public:
	UG1PlayerUserWidget(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	virtual void NativeConstruct() override;

public:
	void SetName(const FString& Name);
	void SetHpRatio(float CurHp, float MaxHp);

protected:
	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
	TObjectPtr<class UTextBlock> PlayerName;

	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
	TObjectPtr<class UProgressBar> HpBar;

	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
	TObjectPtr<class UTextBlock> CurrentHP;

	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
	TObjectPtr<class UTextBlock> MaxHP;
};
