// UhuGameplayAbility.h
// Copyright by MykeUhu

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "UhuGameplayAbility.generated.h"

UCLASS()
class SURVIVAL_API UUhuGameplayAbility : public UGameplayAbility
{
    GENERATED_BODY()

public:
    UUhuGameplayAbility();

    // The level of the ability, used to scale ability effects
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability")
    int32 AbilityLevel = 1;
    
    // Gameplay tags granted to the owner while this ability is active
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability")
    FGameplayTagContainer GrantedTags;
    
    UPROPERTY(EditDefaultsOnly, Category="Input")
    FGameplayTag StartupInputTag;

    // Overrides
    virtual bool CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags = nullptr, const FGameplayTagContainer* TargetTags = nullptr, OUT FGameplayTagContainer* OptionalRelevantTags = nullptr) const override;
    virtual void ApplyCooldown(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) const override;
    virtual void ApplyCost(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) const override;
};