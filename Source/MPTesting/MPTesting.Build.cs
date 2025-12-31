// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class MPTesting : ModuleRules
{
	public MPTesting(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"AIModule",
			"StateTreeModule",
			"GameplayStateTreeModule",
			"UMG",
			"Slate"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"MPTesting",
			"MPTesting/Variant_Platforming",
			"MPTesting/Variant_Platforming/Animation",
			"MPTesting/Variant_Combat",
			"MPTesting/Variant_Combat/AI",
			"MPTesting/Variant_Combat/Animation",
			"MPTesting/Variant_Combat/Gameplay",
			"MPTesting/Variant_Combat/Interfaces",
			"MPTesting/Variant_Combat/UI",
			"MPTesting/Variant_SideScrolling",
			"MPTesting/Variant_SideScrolling/AI",
			"MPTesting/Variant_SideScrolling/Gameplay",
			"MPTesting/Variant_SideScrolling/Interfaces",
			"MPTesting/Variant_SideScrolling/UI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
