// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class ProjectBreakfast : ModuleRules
{
	public ProjectBreakfast(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay" });
	}
}
