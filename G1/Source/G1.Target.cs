// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class G1Target : TargetRules
{
	public G1Target(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V6;
		IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_7;
		ExtraModuleNames.Add("G1");

		// SVC 버전 강제 고정 (핵심)
		WindowsPlatform.Compiler = WindowsCompiler.VisualStudio2022;
		WindowsPlatform.CompilerVersion = "14.44.35207";

		bOverrideBuildEnvironment = true;
		AdditionalCompilerArguments = "/Zc:__STDC__"; // 또는 필요한 경우 표준 라이브러리 강제 링크 설정
	}
}
