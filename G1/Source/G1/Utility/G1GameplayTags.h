// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "NativeGameplayTags.h"

namespace G1GameplayTags
{
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Input_Action_Move);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Input_Action_Turn);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Input_Action_Jump);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Input_Action_Attack);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Input_Action_HitTarget);
}

namespace G1GameplayTags
{
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Event_Montage_Begin);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Event_Montage_End);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Event_Montage_Attack_Start);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Event_Montage_Attack_End);
}

namespace G1GameplayTags
{
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_Attack);
}

namespace G1GameplayTags
{
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Team_None);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Team_Monster);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Team_Player);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Team_Npc);
}