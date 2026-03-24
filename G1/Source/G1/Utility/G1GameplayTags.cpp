// Fill out your copyright notice in the Description page of Project Settings.


#include "Utility/G1GameplayTags.h"

namespace G1GameplayTags
{
	UE_DEFINE_GAMEPLAY_TAG(Input_Action_Move, "Input.Action.Move");
	UE_DEFINE_GAMEPLAY_TAG(Input_Action_Turn, "Input.Action.Turn");
	UE_DEFINE_GAMEPLAY_TAG(Input_Action_Jump, "Input.Action.Jump");
	UE_DEFINE_GAMEPLAY_TAG(Input_Action_Attack, "Input.Action.Attack");
	UE_DEFINE_GAMEPLAY_TAG(Input_Action_HitTarget, "Input.Action.HitTarget");
}

namespace G1GameplayTags
{
	UE_DEFINE_GAMEPLAY_TAG(Event_Montage_Begin, "Event.Montage.Begin");
	UE_DEFINE_GAMEPLAY_TAG(Event_Montage_End, "Event.Montage.End");
	UE_DEFINE_GAMEPLAY_TAG(Event_Montage_Attack_Start, "Event.Montage.Attack.Start");
	UE_DEFINE_GAMEPLAY_TAG(Event_Montage_Attack_End, "Event.Montage.Attack.End");
}

namespace G1GameplayTags
{
	UE_DEFINE_GAMEPLAY_TAG(Ability_Attack, "Ability.Attack");
}

namespace G1GameplayTags
{
	UE_DEFINE_GAMEPLAY_TAG(Team_None, "Team_None");
	UE_DEFINE_GAMEPLAY_TAG(Team_Monster, "Team_Monster");
	UE_DEFINE_GAMEPLAY_TAG(Team_Player, "Team_Player");
	UE_DEFINE_GAMEPLAY_TAG(Team_Npc, "Team_Npc");
}