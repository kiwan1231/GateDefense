// Fill out your copyright notice in the Description page of Project Settings.


#include "Utility/G1GameplayTags.h"

namespace R1GameplayTags
{
	UE_DEFINE_GAMEPLAY_TAG(Input_Action_Move, "Input.Action.Move");
	UE_DEFINE_GAMEPLAY_TAG(Input_Action_Turn, "Input.Action.Turn");
	UE_DEFINE_GAMEPLAY_TAG(Input_Action_Jump, "Input.Action.Jump");
	UE_DEFINE_GAMEPLAY_TAG(Input_Action_Attack, "Input.Action.Attack");

	UE_DEFINE_GAMEPLAY_TAG(Input_Action_SetDestination, "Input.Action.SetDestination");

	UE_DEFINE_GAMEPLAY_TAG(Event_Montage_Begin, "Event.Montage.Begin");
	UE_DEFINE_GAMEPLAY_TAG(Event_Montage_End, "Event.Montage.End");
	UE_DEFINE_GAMEPLAY_TAG(Event_Montage_Attack, "Event.Montage.Attack");

	UE_DEFINE_GAMEPLAY_TAG(Ability_Attack, "Ability.Attack");
}