// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Ingame/G1PlayerUserWidget.h"
#include "G1PlayerUserWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

#include "Character/G1Character.h"
#include "Character/G1Player.h"

UG1PlayerUserWidget::UG1PlayerUserWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UG1PlayerUserWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UG1PlayerUserWidget::OnInitPlayerWidget(AG1Player* Player)
{
	G1Player = Player;

	G1Player->OnAddEquipment.AddUObject(this, &UG1PlayerUserWidget::Delegate_OnAddEquipment);
	G1Player->OnRemoveEquipment.AddUObject(this, &UG1PlayerUserWidget::Delegate_OnRemoveEquipment);
}

void UG1PlayerUserWidget::SetName(const FString& Name)
{
	if (PlayerName != nullptr)
	{
		PlayerName->SetText(FText::FromString(Name));
	}
}

void UG1PlayerUserWidget::SetHpRatio(float CurHp, float MaxHp)
{
	if (CurrentHP != nullptr)
	{
		CurrentHP->SetText(FText::FromString(FString::SanitizeFloat(CurHp)));
	}

	if (MaxHP != nullptr)
	{
		MaxHP->SetText(FText::FromString(FString::SanitizeFloat(MaxHp)));
	}

	if (HpBar != nullptr)
	{
		HpBar->SetPercent(CurHp / MaxHp);
	}
}

void UG1PlayerUserWidget::SetDamage(float Damage)
{
	if (CurrentDamage != nullptr)
	{
		CurrentDamage->SetText(FText::FromString(FString::SanitizeFloat(Damage)));
	}
}

void UG1PlayerUserWidget::Delegate_OnAddEquipment(AG1Character* Character, FName ItemID)
{
	SetDamage(Character->TotalDemage());
}
void UG1PlayerUserWidget::Delegate_OnRemoveEquipment(AG1Character* Character, EEquipmentType EquipType)
{
	SetDamage(Character->TotalDemage());
}
