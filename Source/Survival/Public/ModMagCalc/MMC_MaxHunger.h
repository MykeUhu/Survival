// MMC_MaxHunger.h
// Copyright by MykeUhu

#pragma once

#include "CoreMinimal.h"
#include "GameplayModMagnitudeCalculation.h"
#include "MMC_MaxHunger.generated.h"

/**
 * Calculates the base magnitude for MaxHunger based on the Endurance attribute.
 */
UCLASS()
class SURVIVAL_API UMMC_MaxHunger : public UGameplayModMagnitudeCalculation
{
	GENERATED_BODY()

public:
	UMMC_MaxHunger();

	virtual float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const override;

private:
	FGameplayEffectAttributeCaptureDefinition EnduranceDef;
};
