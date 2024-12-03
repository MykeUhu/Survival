// MMC_MaxHealth.cpp
// Copyright by MykeUhu


#include "ModMagCalc/MMC_MaxHealth.h"

#include "AbilitySystem/UhuAttributeSet.h"

UMMC_MaxHealth::UMMC_MaxHealth()
{
	// Configure the Strength attribute to be captured
	StrengthDef.AttributeToCapture = UUhuAttributeSet::GetStrengthAttribute();
	StrengthDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	StrengthDef.bSnapshot = false;

	// Add the attribute to the list of relevant attributes to capture
	RelevantAttributesToCapture.Add(StrengthDef);
}

float UMMC_MaxHealth::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	// Extract gameplay tags from source and target
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	// Set up parameters for evaluation
	FAggregatorEvaluateParameters EvaluationParameters;
	EvaluationParameters.SourceTags = SourceTags;
	EvaluationParameters.TargetTags = TargetTags;

	// Capture the Strength value
	float Strength = 0.f;
	GetCapturedAttributeMagnitude(StrengthDef, Spec, EvaluationParameters, Strength);
	Strength = FMath::Max<float>(Strength, 0.f);

	// Determine the player's level (default is 1 if not implemented)
	int32 PlayerLevel = 1;

	// TODO: Implement correct player level retrieval if required

	// Return the calculated MaxHealth value
	return 80.f + 2.5f * Strength + 10.f * PlayerLevel;
}
