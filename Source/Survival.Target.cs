// Copyright by MykeUhu

using UnrealBuildTool;
using System.Collections.Generic;

public class SurvivalTarget : TargetRules
{
	public SurvivalTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V5;

		ExtraModuleNames.AddRange( new string[] { "Survival" } );
	}
}
