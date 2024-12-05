// UhuGameplaytags.cpp
// Copyright by MykeUhu

#include "UhuGameplayTags.h"

#include "GameplayTagsManager.h"

FUhuGameplayTags FUhuGameplayTags::GameplayTags;

void FUhuGameplayTags::InitializeNativeGameplayTags()
{
    /*
     * Status
     */
    GameplayTags.Abilities_Status_Equipped = UGameplayTagsManager::Get().AddNativeGameplayTag(
        FName("Abilities.Status.Equipped"),
        FString("Indicates if an ability or item is currently equipped.")
    );

    /*
     * Vital Attributes
     */
    GameplayTags.Attribute_Vital_Health = UGameplayTagsManager::Get().AddNativeGameplayTag(
        FName("Attribute.Vital.Health"),
        FString("Represents the health of the character.")
    );
    GameplayTags.Attribute_Vital_Hunger = UGameplayTagsManager::Get().AddNativeGameplayTag(
        FName("Attribute.Vital.Hunger"),
        FString("Represents the hunger level of the character.")
    );
    GameplayTags.Attribute_Vital_Thirst = UGameplayTagsManager::Get().AddNativeGameplayTag(
        FName("Attribute.Vital.Thirst"),
        FString("Represents the thirst level of the character.")
    );
    GameplayTags.Attribute_Vital_Stamina = UGameplayTagsManager::Get().AddNativeGameplayTag(
        FName("Attribute.Vital.Stamina"),
        FString("Represents the stamina of the character.")
    );
    GameplayTags.Attribute_Vital_Temperature = UGameplayTagsManager::Get().AddNativeGameplayTag(
        FName("Attribute.Vital.Temperature"),
        FString("Represents the temperature of the character.")
    );

    /*
     * Vital Max Attributes
     */
    GameplayTags.Attribute_Vital_MaxHealth = UGameplayTagsManager::Get().AddNativeGameplayTag(
        FName("Attribute.Vital.MaxHealth"),
        FString("Represents the maximum health value.")
    );
    GameplayTags.Attribute_Vital_MaxHunger = UGameplayTagsManager::Get().AddNativeGameplayTag(
        FName("Attribute.Vital.MaxHunger"),
        FString("Represents the maximum hunger value.")
    );
    GameplayTags.Attribute_Vital_MaxThirst = UGameplayTagsManager::Get().AddNativeGameplayTag(
        FName("Attribute.Vital.MaxThirst"),
        FString("Represents the maximum thirst value.")
    );
    GameplayTags.Attribute_Vital_MaxStamina = UGameplayTagsManager::Get().AddNativeGameplayTag(
        FName("Attribute.Vital.MaxStamina"),
        FString("Represents the maximum stamina value.")
    );

    /*
     * Primary Attributes
     */
    GameplayTags.Attribute_Primary_Endurance = UGameplayTagsManager::Get().AddNativeGameplayTag(
        FName("Attribute.Primary.Endurance"),
        FString("Increases max hunger and health regeneration. Affected by Cleanliness and Perception.")
    );
    GameplayTags.Attribute_Primary_Strength = UGameplayTagsManager::Get().AddNativeGameplayTag(
        FName("Attribute.Primary.Strength"),
        FString("Increases max health and hunger regeneration. Affected by Communication and Survivability.")
    );
    GameplayTags.Attribute_Primary_Agility = UGameplayTagsManager::Get().AddNativeGameplayTag(
        FName("Attribute.Primary.Agility"),
        FString("Increases max thirst and thirst regeneration. Affected by Cleverness and Botany.")
    );
    GameplayTags.Attribute_Primary_Intelligence = UGameplayTagsManager::Get().AddNativeGameplayTag(
        FName("Attribute.Primary.Intelligence"),
        FString("Increases max stamina and stamina regeneration. Affected by Engineering and Technology.")
    );

    /*
     * Secondary Attributes
     */
    GameplayTags.Attribute_Secondary_Cleverness = UGameplayTagsManager::Get().AddNativeGameplayTag(
        FName("Attribute.Secondary.Cleverness"),
        FString("Represents the cleverness of the character.")
    );
    GameplayTags.Attribute_Secondary_Cleanliness = UGameplayTagsManager::Get().AddNativeGameplayTag(
        FName("Attribute.Secondary.Cleanliness"),
        FString("Represents the cleanliness of the character.")
    );
    GameplayTags.Attribute_Secondary_Perception = UGameplayTagsManager::Get().AddNativeGameplayTag(
        FName("Attribute.Secondary.Perception"),
        FString("Represents the perception of the character.")
    );
    GameplayTags.Attribute_Secondary_Communication = UGameplayTagsManager::Get().AddNativeGameplayTag(
        FName("Attribute.Secondary.Communication"),
        FString("Represents the communication skills of the character.")
    );
    GameplayTags.Attribute_Secondary_Survivability = UGameplayTagsManager::Get().AddNativeGameplayTag(
        FName("Attribute.Secondary.Survivability"),
        FString("Represents the survivability of the character.")
    );
    GameplayTags.Attribute_Secondary_Engineering = UGameplayTagsManager::Get().AddNativeGameplayTag(
        FName("Attribute.Secondary.Engineering"),
        FString("Represents the engineering skills of the character.")
    );
    GameplayTags.Attribute_Secondary_Botany = UGameplayTagsManager::Get().AddNativeGameplayTag(
        FName("Attribute.Secondary.Botany"),
        FString("Represents the botany skills of the character.")
    );
    GameplayTags.Attribute_Secondary_Technology = UGameplayTagsManager::Get().AddNativeGameplayTag(
        FName("Attribute.Secondary.Technology"),
        FString("Represents the technology skills of the character.")
    );

    /*
     * Resistances
     */
    GameplayTags.Resistances_ResTemperature = UGameplayTagsManager::Get().AddNativeGameplayTag(
        FName("Resistances.ResTemperature"),
        FString("Represents resistance to heat and cold.")
    );

    /*
     * Buffs
     */
    GameplayTags.Buff_HealthRegeneration = UGameplayTagsManager::Get().AddNativeGameplayTag(
        FName("Buff.HealthRegeneration"),
        FString("Increases health regeneration rate.")
    );
    GameplayTags.Buff_HungerRegeneration = UGameplayTagsManager::Get().AddNativeGameplayTag(
        FName("Buff.HungerRegeneration"),
        FString("Increases hunger regeneration rate.")
    );
    GameplayTags.Buff_ThirstRegeneration = UGameplayTagsManager::Get().AddNativeGameplayTag(
        FName("Buff.ThirstRegeneration"),
        FString("Increases thirst regeneration rate.")
    );
    GameplayTags.Buff_StaminaRegeneration = UGameplayTagsManager::Get().AddNativeGameplayTag(
        FName("Buff.StaminaRegeneration"),
        FString("Increases stamina regeneration rate.")
    );

    /*
     * DeBuffs
     */
    GameplayTags.DeBuff_HealthDegeneration = UGameplayTagsManager::Get().AddNativeGameplayTag(
        FName("DeBuff.HealthDegeneration"),
        FString("Decreases health over time due to adverse conditions.")
    );
    GameplayTags.DeBuff_HungerDegeneration = UGameplayTagsManager::Get().AddNativeGameplayTag(
        FName("DeBuff.HungerDegeneration"),
        FString("Decreases hunger over time.")
    );
    GameplayTags.DeBuff_ThirstDegeneration = UGameplayTagsManager::Get().AddNativeGameplayTag(
        FName("DeBuff.ThirstDegeneration"),
        FString("Decreases thirst over time.")
    );
    GameplayTags.DeBuff_StaminaDegeneration = UGameplayTagsManager::Get().AddNativeGameplayTag(
        FName("DeBuff.StaminaDegeneration"),
        FString("Decreases stamina over time.")
    );

    /*
     * Movement
     */
    // Movement Speed Tags
    GameplayTags.Movement_Speed_0 = UGameplayTagsManager::Get().AddNativeGameplayTag(
	    FName("Movement.Speed.0"),
	    FString("Player is standing still. WalkSpeed = 0; can regenerate 10 Stamina per 10 seconds if Hunger and Thirst are sufficient.")
    );

    GameplayTags.Movement_Speed_1 = UGameplayTagsManager::Get().AddNativeGameplayTag(
	    FName("Movement.Speed.1"),
	    FString("Player is slow walking. WalkSpeed = 100; can regenerate 5 Stamina per 10 seconds if Hunger and Thirst are sufficient.")
    );

    GameplayTags.Movement_Speed_2 = UGameplayTagsManager::Get().AddNativeGameplayTag(
	    FName("Movement.Speed.2"),
	    FString("Player is walking. WalkSpeed = 200; can regenerate 3 Stamina per 10 seconds if Hunger and Thirst are sufficient.")
    );

    GameplayTags.Movement_Speed_3 = UGameplayTagsManager::Get().AddNativeGameplayTag(
	    FName("Movement.Speed.3"),
	    FString("Player is fast walking. WalkSpeed = 300; can regenerate 2 Stamina per 10 seconds if Hunger and Thirst are sufficient.")
    );

    GameplayTags.Movement_Speed_4 = UGameplayTagsManager::Get().AddNativeGameplayTag(
	    FName("Movement.Speed.4"),
	    FString("Player is jogging. WalkSpeed = 400; can regenerate 1 Stamina per 10 seconds if Hunger and Thirst are sufficient.")
    );

    GameplayTags.Movement_Speed_5 = UGameplayTagsManager::Get().AddNativeGameplayTag(
	    FName("Movement.Speed.5"),
	    FString("Player is slow running. WalkSpeed = 500; no stamina regeneration or degeneration.")
    );

    GameplayTags.Movement_Speed_6 = UGameplayTagsManager::Get().AddNativeGameplayTag(
	    FName("Movement.Speed.6"),
	    FString("Player is running. WalkSpeed = 600; degenerates 1 Stamina per 10 seconds. If Stamina <= 0, speed resets to Level 5.")
    );

    GameplayTags.Movement_Speed_7 = UGameplayTagsManager::Get().AddNativeGameplayTag(
	    FName("Movement.Speed.7"),
	    FString("Player is fast running. WalkSpeed = 700; degenerates 2 Stamina per 10 seconds. If Stamina <= 0, speed resets to Level 5.")
    );

    GameplayTags.Movement_Speed_8 = UGameplayTagsManager::Get().AddNativeGameplayTag(
	    FName("Movement.Speed.8"),
	    FString("Player is very fast running. WalkSpeed = 800; degenerates 3 Stamina per 10 seconds. If Stamina <= 0, speed resets to Level 5.")
    );

    GameplayTags.Movement_Speed_9 = UGameplayTagsManager::Get().AddNativeGameplayTag(
	    FName("Movement.Speed.9"),
	    FString("Player is ultra fast running. WalkSpeed = 900; degenerates 5 Stamina per 10 seconds. If Stamina <= 0, speed resets to Level 5.")
    );

    GameplayTags.Movement_Speed_10 = UGameplayTagsManager::Get().AddNativeGameplayTag(
	    FName("Movement.Speed.10"),
	    FString("Player is extremely fast (Flash-level). WalkSpeed = 1000; degenerates 10 Stamina per 10 seconds. If Stamina <= 0, speed resets to Level 5.")
    );
	
    // Movement States
	GameplayTags.Movement_IsStandStill = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Movement.IsStandStill"),
		FString("Player is standing still.")
	);

	GameplayTags.Movement_IsWalking = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Movement.IsWalking"),
		FString("Player is walking.")
	);

	GameplayTags.Movement_IsRunning = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Movement.IsRunning"),
		FString("Player is running.")
	);

	GameplayTags.Movement_IsSprinting = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Movement.IsSprinting"),
		FString("Player is sprinting.")
	);

	// Movement Capabilities
	GameplayTags.Movement_CanStandStill = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Movement.CanStandStill"),
		FString("Player can stand still.")
	);

	GameplayTags.Movement_CanWalk = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Movement.CanWalk"),
		FString("Player can walk.")
	);

	GameplayTags.Movement_CanRun = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Movement.CanRun"),
		FString("Player can run.")
	);

	GameplayTags.Movement_CanSprint = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Movement.CanSprint"),
		FString("Player can sprint.")
	);

	/*
	 * Abilities
	 */
	// Meta
	GameplayTags.Abilities_Status_Unlocked = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Abilities.Status.Unlocked"),
	FString("Indicates that a certain ability status has been unlocked.")
	);

	GameplayTags.Abilities_None = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Abilities.None"),
		FString("Represents the absence of any abilities.")
	);
	
	GameplayTags.Abilities_Status_Eligible = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Abilities.Status.Eligible"),
		FString("need Description")
	);

	GameplayTags.Abilities_Type_Passive = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Abilities.Type.Passive"),
		FString("need Description")
	);

	// Other
	GameplayTags.Ability_Survival_FindConsumables = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Ability.Survival.FindConsumables"),
		FString("Marks food or water sources in the area with an outline for a certain duration.")
	);

	GameplayTags.Ability_Drone_Gathering = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Ability.Drone.Gathering"),
		FString("Drone gathers resources using AI and delivers them to storage or construction sites.")
	);

	GameplayTags.Ability_Drone_Blueprint = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Ability.Drone.Blueprint"),
		FString("Drone sets a blueprint for building construction.")
	);

	GameplayTags.Ability_Drone_Build = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Ability.Drone.Build"),
		FString("Drone builds at an open construction site.")
	);

	GameplayTags.Ability_Hologram_Vitals = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Ability.Hologram.Vitals"),
		FString("Projects the character's vital values as a hologram.")
	);

	GameplayTags.Ability_Hologram_Botany = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Ability.Hologram.Botany"),
		FString("Displays information about plants, food, and the environment using a hologram.")
	);

	/*
	 * Drone Communication Tags
	 */
	GameplayTags.Emote_DroneCommand_Sleep = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Emote.DroneCommand.Sleep"),
		FString("Command the drone to set up a sleep place")
	);
	GameplayTags.Emote_DroneCommand_Gather = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Emote.DroneCommand.Gather"),
		FString("Command the drone to gather resources")
	);
	GameplayTags.Emote_DroneCommand_Build = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Emote.DroneCommand.Build"),
		FString("Command the drone to build structures")
	);
	GameplayTags.Emote_DroneCommand_Scan = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Emote.DroneCommand.Scan"),
		FString("Command the drone to scan the environment")
	);

	/*
	 * Skill System Tags
	 */
	GameplayTags.Skill_Running = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Skill.Running"),
		FString("Running skill progression")
	);
	GameplayTags.Skill_Walking = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Skill.Walking"),
		FString("Walking skill progression")
	);
	GameplayTags.Skill_Crafting = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Skill.Crafting"),
		FString("Crafting skill progression")
	);
	GameplayTags.Skill_Survival = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Skill.Survival"),
		FString("Survival skill progression")
	);
}
