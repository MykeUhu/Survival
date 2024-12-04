// UhuGameplaytags.h
// Copyright by MykeUhu
// TODO: Remember, use GameplayTags and Effects, because its the most powerfull Tool in Unreal Engine
#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"

struct FUhuGameplayTags
{
public:
	static const FUhuGameplayTags& Get() { return GameplayTags; }
	static void InitializeNativeGameplayTags();
	// TODO: Remember, use GameplayTags and Effects, because its the most powerfull Tool in Unreal Engine
	/*
	* Status
	*/
	FGameplayTag Abilities_Status_Equipped;

	/*
	* Vital Attributes
	*/
	FGameplayTag Attribute_Vital_Health;
	FGameplayTag Attribute_Vital_Hunger;
	FGameplayTag Attribute_Vital_Thirst;
	FGameplayTag Attribute_Vital_Stamina;
	FGameplayTag Attribute_Vital_Temperature;

	/*
	* Vital Max Attributes
	*/
	FGameplayTag Attribute_Vital_MaxHealth;
	FGameplayTag Attribute_Vital_MaxHunger;
	FGameplayTag Attribute_Vital_MaxThirst;
	FGameplayTag Attribute_Vital_MaxStamina;

	/*
	* Primnary Attribute
	*/
	FGameplayTag Attribute_Primary_Endurance;		// Bonus: MaxHunger, HealthRegeneration				// Gesteigert durch: Cleanliness, Perception
	FGameplayTag Attribute_Primary_Strength;		// Bonus: MaxHealth, HungerRegeneration				// Gesteigert durch: Communication, Survivability
	FGameplayTag Attribute_Primary_Agility;			// Bonus: MaxStamina, ThirstRegeneration			// Gesteigert durch: Cleverness, Botany
	FGameplayTag Attribute_Primary_Intelligence;	// Bonus: MaxThirst, StaminaRegeneration			// Gesteigert durch: Engineering, Technology
	

	/*
	* Secondary Attribute
	*/
	FGameplayTag Attribute_Secondary_Cleverness;
	FGameplayTag Attribute_Secondary_Cleanliness;
	FGameplayTag Attribute_Secondary_Perception;
	FGameplayTag Attribute_Secondary_Communication;
	FGameplayTag Attribute_Secondary_Survivability;
	FGameplayTag Attribute_Secondary_Engineering;
	FGameplayTag Attribute_Secondary_Botany;
	FGameplayTag Attribute_Secondary_Technology;
	
	/*
	* Resistances
	*/
	FGameplayTag Resistances_ResTemperature;			// Heatstroke and Cold Resistances

	/*
	* Buff
	*/
	FGameplayTag Buff_HealthRegeneration;			// For GE_HealthRegeneration (10 Hunger Regneration per 10 Seconds -> (3/5 DeBuff_HungerDegeneration[GE_DeBuff_HungerDegeneration] + 2/5 DeBuff_ThirstDegeneration[GE_DeBuff_ThirstDegeneration])
	FGameplayTag Buff_HungerRegeneration;			// For GE_HungerRegeneration (When you eat an apple, for example, the hunger is satisfied with the value stored in the apple.
	FGameplayTag Buff_ThirstRegeneration;			// For GE_ThirstRegeneration (When you drink water, your thirst is quenched.)
	FGameplayTag Buff_StaminaRegeneration;			// For GE_StaminaRegeneration (10 Stamina Regneration per 10 Seconds -> (2/5 DeBuff_HungerDegeneration[GE_DeBuff_HungerDegeneration] + 3/5 DeBuff_ThirstDegeneration[GE_DeBuff_ThirstDegeneration])

	/*
	* DeBuff
	*/
	FGameplayTag DeBuff_HealthDegeneration;			// Required for starvation, dehydration, or other harmful conditions
	FGameplayTag DeBuff_HungerDegeneration;			// Required for HealthRegeneration, StaminaRegeneration, ...
	FGameplayTag DeBuff_ThirstDegeneration;			// Required for HealthRegeneration, StaminaRegeneration, ...
	FGameplayTag DeBuff_StaminaDegeneration;		// Required for Movement Speed above 
	
	/*
	* Movement
	*/
	FGameplayTag Movement_Speed_0;					//Tag for Player: Movement_IsStandStill		// WalkSpeed 000;		-> Stand still					-> can Regenerate 10 Stamina per 10 Seconds (if enough Hunger and Thirst, if one of these stop Regeneration)
	FGameplayTag Movement_Speed_1;					//Tag for Player: Movement_IsWalking		// WalkSpeed 100;		-> Slow walking					-> can Regenerate 5 Stamina per 10 Seconds (if enough Hunger and Thirst, if one of these stop Regeneration)
	FGameplayTag Movement_Speed_2;					//Tag for Player: Movement_IsWalking		// WalkSpeed 200;		-> walking						-> can Regenerate 3 Stamina per 10 Seconds (if enough Hunger and Thirst, if one of these stop Regeneration)
	FGameplayTag Movement_Speed_3;					//Tag for Player: Movement_IsWalking		// WalkSpeed 300;		-> fast walking					-> can Regenerate 2 Stamina per 10 Seconds (if enough Hunger and Thirst, if one of these stop Regeneration)
	FGameplayTag Movement_Speed_4;					//Tag for Player: Movement_IsWalking		// WalkSpeed 400;		-> Jog							-> can Regenerate 1 Stamina per 10 Seconds (if enough Hunger and Thirst, if one of these stop Regeneration)
	FGameplayTag Movement_Speed_5;					//Tag for Player: Movement_IsRunning		// WalkSpeed 500;		-> slow running					-> no Regenerate Stamina, no Degenerate Stamina 
	FGameplayTag Movement_Speed_6;					//Tag for Player: Movement_IsSprinting		// WalkSpeed 600;		-> running						-> Degenerate 1 Stamina per 10 Seconds ( if Stamina <= 0 -> deactivate Movementspeed above Level5, Set Movementspeed to Level 5, Remove GameplayTag -> Can Sprint)
	FGameplayTag Movement_Speed_7;					//Tag for Player: Movement_IsSprinting		// WalkSpeed 700;		-> fast running					-> Degenerate 2 Stamina per 10 Seconds (if Stamina <= 0 -> deactivate Movementspeed above Level5, Set Movementspeed to Level 5, Remove GameplayTag -> Can Sprint)
	FGameplayTag Movement_Speed_8;					//Tag for Player: Movement_IsSprinting		// WalkSpeed 800;		-> very fast running			-> Degenerate 3 Stamina per 10 Seconds (if Stamina <= 0 -> deactivate Movementspeed above Level5, Set Movementspeed to Level 5, Remove GameplayTag -> Can Sprint)
	FGameplayTag Movement_Speed_9;					//Tag for Player: Movement_IsSprinting		// WalkSpeed 900;		-> ultra fast running			-> Degenerate 5 Stamina per 10 Seconds (if Stamina <= 0 -> deactivate Movementspeed above Level5, Set Movementspeed to Level 5, Remove GameplayTag -> Can Sprint)
	FGameplayTag Movement_Speed_10;					//Tag for Player: Movement_IsSprinting		// WalkSpeed 1000;		-> are you Flash?				-> Degenerate 10 Stamina per 10 Seconds (if Stamina <= 0 -> deactivate Movementspeed above Level5, Set Movementspeed to Level 5, Remove GameplayTag -> Can Sprint)

	FGameplayTag Movement_IsStandStill;
	FGameplayTag Movement_IsWalking;
	FGameplayTag Movement_IsRunning;
	FGameplayTag Movement_IsSprinting;

	FGameplayTag Movement_CanStandStill;
	FGameplayTag Movement_CanWalk;
	FGameplayTag Movement_CanRun;
	FGameplayTag Movement_CanSprint;
	
	/*
	* Ability
	*/

	// Meta

	FGameplayTag Abilities_None;
	FGameplayTag Abilities_Status_Unlocked;
	// Other
	FGameplayTag Ability_Survival_FindConsumables;  // Survival-Nahrung oder Wasser entdecken: Markiert Nahrung oder Wasserquellen in der Umgebung durch Outline für gewisse Zeit

	FGameplayTag Ability_Drone_Gathering;           // Emote-Ressourcen sammeln Befehl an Drohne: Sammelt mit AI Resourcen und bringt sie ins Lager oder offene Baustellen
	FGameplayTag Ability_Drone_Blueprint;           // Drohne-Blueprint setzen: Setzt einen Blueprint für den Bau eines Gebäudes
	FGameplayTag Ability_Drone_Build;               // Drohne baut offene Baustelle

	FGameplayTag Ability_Hologram_Vitals;           // Hologramm für Vitalwerte: Projiziert die Vitalwerte des Charakters als Hologramm
	FGameplayTag Ability_Hologram_Botany;           // Emote-Botanik: Zeigt Informationen über Pflanzen, Nahrung usw. in der Umgebung an durch Hologramm

	/*
	* Drone Communication Tags
	*/
	FGameplayTag Emote_DroneCommand_Sleep;
	FGameplayTag Emote_DroneCommand_Gather;
	FGameplayTag Emote_DroneCommand_Build;
	FGameplayTag Emote_DroneCommand_Scan;

	/*
	* Skill System Tags
	*/
	FGameplayTag Skill_Running;
	FGameplayTag Skill_Walking;
	FGameplayTag Skill_Crafting;
	FGameplayTag Skill_Survival;

private:
	static FUhuGameplayTags GameplayTags;
	
};