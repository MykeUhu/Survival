// MMC_MaxThirst.cpp
// Copyright by MykeUhu

#include "ModMagCalc/MMC_MaxThirst.h"

#include "AbilitySystem/UhuAttributeSet.h"

UMMC_MaxThirst::UMMC_MaxThirst()
{
	IntelligenceDef.AttributeToCapture = UUhuAttributeSet::GetIntelligenceAttribute();
	IntelligenceDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	IntelligenceDef.bSnapshot = false;

	RelevantAttributesToCapture.Add(IntelligenceDef);
}

float UMMC_MaxThirst::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluationParameters;
	EvaluationParameters.SourceTags = SourceTags;
	EvaluationParameters.TargetTags = TargetTags;

	float Intelligence = 0.f;
	GetCapturedAttributeMagnitude(IntelligenceDef, Spec, EvaluationParameters, Intelligence);
	Intelligence = FMath::Max<float>(Intelligence, 0.f);

	int32 PlayerLevel = 1;

	// TODO: Implement player level retrieval if necessary

	return 70.f + 1.5f * Intelligence + 12.f * PlayerLevel;
}
