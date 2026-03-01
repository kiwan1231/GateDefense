// Copyright Epic Games, Inc. All Rights Reserved.

#include "G1.h"
#include "Modules/ModuleManager.h"

class FG1Module : public FDefaultGameModuleImpl
{
	virtual void StartupModule() override
	{

	}

	virtual void ShutdownModule() override
	{

	}
};

IMPLEMENT_PRIMARY_GAME_MODULE(FG1Module, G1, "G1" );
