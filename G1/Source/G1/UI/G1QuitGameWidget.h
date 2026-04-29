// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/G1UserWidget.h"
#include "G1QuitGameWidget.generated.h"

class UButton;
class UTextBlock;

UCLASS()
class G1_API UG1QuitGameWidget : public UG1UserWidget
{
	GENERATED_BODY()
	
protected:
    virtual bool Initialize() override;

    // UI 바인딩
    UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
    UButton* YesButton;

    UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
    UButton* NoButton;

    UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
    UTextBlock* QuitText;

    // 클릭 함수
    UFUNCTION()
    void OnClickYes();

    UFUNCTION()
    void OnClickNo();

};
