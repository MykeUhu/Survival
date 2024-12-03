// MMC_MaxThirst.h
// Copyright by MykeUhu

#pragma once

#include "CoreMinimal.h"
#include "GameplayModMagnitudeCalculation.h"
#include "MMC_MaxThirst.generated.h"

/**
 * Calculates the base magnitude for MaxThirst based on the Intelligence attribute.
 */
UCLASS()
class SURVIVAL_API UMMC_MaxThirst : public UGameplayModMagnitudeCalculation
{
	GENERATED_BODY()

public:
	UMMC_MaxThirst();

	virtual float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const override;

private:
	FGameplayEffectAttributeCaptureDefinition IntelligenceDef;
};
