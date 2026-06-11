// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class HeliconUnreal : ModuleRules
{
	public HeliconUnreal(ReadOnlyTargetRules Target) : base(Target)
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
			"Slate",
			"Niagara"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"HeliconUnreal",
			"HeliconUnreal/Variant_Horror",
			"HeliconUnreal/Variant_Horror/UI",
			"HeliconUnreal/Variant_Shooter",
			"HeliconUnreal/Variant_Shooter/AI",
			"HeliconUnreal/Variant_Shooter/UI",
			"HeliconUnreal/Variant_Shooter/Weapons"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
