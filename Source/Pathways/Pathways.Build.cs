// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Pathways : ModuleRules
{
	public Pathways(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] {
            "Core",
            "CoreUObject",
            "Engine",
            "InputCore",
            "EnhancedInput",
            "Json",          // Add this line
            "JsonUtilities"  // Add this line
        });

    }
}
