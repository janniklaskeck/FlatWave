// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class FlatWave : ModuleRules
{
    public FlatWave(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] {
            "Core",
            "CoreUObject",
            "Engine",
            "InputCore",
            "UMG",
            "AIModule",
            "GameplayTasks",
            "NavigationSystem"
        });

        PrivateIncludePaths.AddRange(new string[]
        {
            "FlatWave/Characters",
            "FlatWave/Characters/Player",
            "FlatWave/Characters/Enemy",
            "FlatWave/Characters/Enemy/BehaviorTasks",
            "FlatWave/Weapons",
            "FlatWave/Weapons/Projectiles",
            "FlatWave/Weapons/Minigun",
            "FlatWave/Weapons/RocketLauncher",
            "FlatWave/Weapons/LaserRifle",
            "FlatWave/Util",
            "FlatWave/Spawner",
            "FlatWave/GameMode",
        });
    }
}
