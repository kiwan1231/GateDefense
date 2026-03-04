// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/G1PlayerInputData.h"

const UInputAction* UG1PlayerInputData::FindInputActionByTag(const FGameplayTag& InputTag) const
{
	for (const FG1InputAction& Action : InputActions)
	{
		if (Action.InputAction && Action.InputTag == InputTag)
		{
			return Action.InputAction;
		}
	}

	UE_LOG(LogTemp, Error, TEXT("Can't find InputAction [%s]"), *InputTag.ToString());

	return nullptr;
}