// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Ingame/G1GameOverSceneWidget.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"

UG1GameOverSceneWidget::UG1GameOverSceneWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	
}

void UG1GameOverSceneWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// 키 입력 받기 위해 필요
	FInputModeUIOnly InputMode;
	InputMode.SetWidgetToFocus(TakeWidget());
	GetOwningPlayer()->SetInputMode(InputMode);
	SetIsFocusable(true);

	// 포커스 강제로 줌
	//FSlateApplication::Get().SetKeyboardFocus(TakeWidget());

	ElapsedTime = 0;
	Presskey->SetVisibility(ESlateVisibility::Hidden);
}

void UG1GameOverSceneWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	ElapsedTime = FMath::Clamp(ElapsedTime + InDeltaTime, 0, 100);

	if (EnableRestart == false && ElapsedTime > 2)
	{
		EnableRestart = true;
		Presskey->SetVisibility(ESlateVisibility::Visible);
	}
}

FReply UG1GameOverSceneWidget::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	if (EnableRestart == false)
	{
		return FReply::Handled();
	}

	// 아무 키나 눌리면
	UGameplayStatics::OpenLevel(this, FName(*UGameplayStatics::GetCurrentLevelName(this, true)));
	return FReply::Handled();
}
