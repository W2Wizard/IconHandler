// Copyright (c) W2.Wizard 2020-2021. All Rights Reserved.

using UnrealBuildTool;

public class IconHandler : ModuleRules
{
	public IconHandler(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange( new[] { "Core" });
			
		
		PrivateDependencyModuleNames.AddRange( new[]
		{
			"CoreUObject",
			"Engine",
			"Slate",
			"SlateCore",
			"Projects"
		});
	}
}
