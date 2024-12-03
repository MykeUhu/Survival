// MMC_MaxHunger.cpp
// Copyright by MykeUhu

#include "ModMagCalc/MMC_MaxHunger.h"

#include "AbilitySystem/UhuAttributeSet.h"

UMMC_MaxHunger::UMMC_MaxHunger()
{
	EnduranceDef.AttributeToCapture = UUhuAttributeSet::GetEnduranceAttribute();
	EnduranceDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	EnduranceDef.bSnapshot = false;

	RelevantAttributesToCapture.Add(EnduranceDef);
}

float UMMC_MaxHunger::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluationParameters;
	EvaluationParameters.SourceTags = SourceTags;
	EvaluationParameters.TargetTags = TargetTags;

	float Endurance = 0.f;
	GetCapturedAttributeMagnitude(EnduranceDef, Spec, EvaluationParameters, Endurance);
	Endurance = FMath::Max<float>(Endurance, 0.f);

	int32 PlayerLevel = 1;

	// TODO: Implement player level retrieval if necessary

	return 50.f + 3.0f * Endurance + 5.f * PlayerLevel;
}
