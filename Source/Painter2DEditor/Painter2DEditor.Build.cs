// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Painter2DEditor : ModuleRules
{
	public Painter2DEditor(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicIncludePaths.AddRange(
			new string[] {
				"Painter2DEditor/Public"
				// ... add public include paths required here ...
			}
			);
				
		
		PrivateIncludePaths.AddRange(
			new string[] {
				"Painter2DEditor/Private",
				// ... add other private include paths required here ...
			}
			);
			
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"Projects"
				// ... add other public dependencies that you statically link with here ...
			}
			);

        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                "CoreUObject",
                "Engine",
                "UnrealEd",
                "EditorStyle",
                "Slate",
                "InputCore",
                "SlateCore",
                "Painter2D",
            });
    }
}
