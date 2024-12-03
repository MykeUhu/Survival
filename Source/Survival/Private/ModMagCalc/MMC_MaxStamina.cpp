// MMC_MaxStamina.cpp
// Copyright by MykeUhu


#include "ModMagCalc/MMC_MaxStamina.h"

#include "AbilitySystem/UhuAttributeSet.h"

UMMC_MaxStamina::UMMC_MaxStamina()
{
	AgilityDef.AttributeToCapture = UUhuAttributeSet::GetAgilityAttribute();
	AgilityDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	AgilityDef.bSnapshot = false;

	RelevantAttributesToCapture.Add(AgilityDef);
}

float UMMC_MaxStamina::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluationParameters;
	EvaluationParameters.SourceTags = SourceTags;
	EvaluationParameters.TargetTags = TargetTags;

	float Agility = 0.f;
	GetCapturedAttributeMagnitude(AgilityDef, Spec, EvaluationParameters, Agility);
	Agility = FMath::Max<float>(Agility, 0.f);

	int32 PlayerLevel = 1;

	// TODO: Implement player level retrieval if necessary

	return 60.f + 2.0f * Agility + 8.f * PlayerLevel;
}
