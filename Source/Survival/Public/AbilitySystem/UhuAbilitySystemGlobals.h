// UhuAbilitySystemGlobals.h
// Copyright by MykeUhu

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemGlobals.h"
#include "UhuAbilitySystemGlobals.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVAL_API UUhuAbilitySystemGlobals : public UAbilitySystemGlobals
{
	GENERATED_BODY()
	virtual FGameplayEffectContext* AllocGameplayEffectContext() const override;
};