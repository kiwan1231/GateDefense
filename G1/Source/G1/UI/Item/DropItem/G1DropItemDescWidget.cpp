// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Item/DropItem/G1DropItemDescWidget.h"
#include "Components/TextBlock.h"

#include "Item/G1EquipmentItem.h"
#include "Data/G1ItemData.h"
#include "System/G1AssetManager.h"

#include "AbilitySystem/Attributes/G1AttributeSet.h"

UG1DropItemDescWidget::UG1DropItemDescWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UG1DropItemDescWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UG1DropItemDescWidget::SetItem(const FName ItemID)
{
	CurrentItemID = ItemID;
	const UG1ItemData* ItemData = UG1AssetManager::GetAssetByName<UG1ItemData>("Item_Weapon");
	if (ItemData == nullptr)
	{
		return;
	}
	const FG1ItemInfo* Info = ItemData->FindItemInfo(ItemID);
	if (Info == nullptr)
	{
		return;
	}
	ItemName->SetText(FText::FromName(Info->ItemID));
	ItemType->SetText(FText::FromString(UEnum::GetValueAsString(Info->ItemType)));
	ItemDesc->SetText(Info->ItemDesc);

	if (Info->ItemEffect != nullptr)
	{
		const UGameplayEffect* EffectCDO = Info->ItemEffect->GetDefaultObject<UGameplayEffect>();
		FString AttributeString;

		for (const FGameplayModifierInfo& Modifier : EffectCDO->Modifiers)
		{
			if (Modifier.Attribute.IsValid())
			{
				FString AttrName = Modifier.Attribute.GetName();
				float Value = 0.0f;

				// ModifierMagnitude에서 값을 추출
				if (Modifier.ModifierMagnitude.GetStaticMagnitudeIfPossible(1.0f, Value))
				{
					AttributeString += FString::Printf(TEXT("%s: %.2f\n"), *AttrName, Value);
				}
				else
				{
					AttributeString += FString::Printf(TEXT("%s: (동적)\n"), *AttrName);
				}
			}
		}

		if (AttributeString.IsEmpty())
		{
			AttributeString = TEXT("속성 없음");
		}

		ItemAttribute->SetText(FText::FromString(AttributeString));
	}
}

void UG1DropItemDescWidget::Show()
{
	SetVisibility(ESlateVisibility::Visible);
}

void UG1DropItemDescWidget::Hide()
{
	SetVisibility(ESlateVisibility::Hidden);
}

void UG1DropItemDescWidget::UpdatePosition(const FVector& WorldLocation)
{
	APlayerController* PC = GetOwningPlayer();
	if (!PC) return;

	FVector2D ScreenPos;
	PC->ProjectWorldLocationToScreen(WorldLocation, ScreenPos);

	// 오른쪽으로 살짝 이동
	ScreenPos.X += 50.0f;

	SetPositionInViewport(ScreenPos);
}
