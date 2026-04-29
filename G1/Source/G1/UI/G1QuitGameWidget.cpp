// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/G1QuitGameWidget.h"

#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Kismet/KismetSystemLibrary.h"

bool UG1QuitGameWidget::Initialize()
{
    bool Success = Super::Initialize();
    if (!Success) return false;

    if (YesButton)
        YesButton->OnClicked.AddDynamic(this, &UG1QuitGameWidget::OnClickYes);

    if (NoButton)
        NoButton->OnClicked.AddDynamic(this, &UG1QuitGameWidget::OnClickNo);

    if (QuitText)
        QuitText->SetText(FText::FromString(TEXT("Game End ?")));

    return true;
}

void UG1QuitGameWidget::OnClickYes()
{
    APlayerController* PC = GetWorld()->GetFirstPlayerController();

    UKismetSystemLibrary::QuitGame(
        this,
        PC,
        EQuitPreference::Quit,
        true
    );
}

void UG1QuitGameWidget::OnClickNo()
{
    Hide();
    //RemoveFromParent(); // UI ´Ý±â
}
