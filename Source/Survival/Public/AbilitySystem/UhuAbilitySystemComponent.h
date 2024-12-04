// UhuAbilitySystemComponent.h
// Copyright by MykeUhu

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "UhuAbilitySystemComponent.generated.h"

UCLASS()
class SURVIVAL_API UUhuAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	UUhuAbilitySystemComponent();

	virtual void InitializeComponent() override;
	void InitializeAttributes();
	void GiveStartupAbilities();

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerApplyAttributePoint(FGameplayAttribute Attribute, float Value);

private:
	UPROPERTY(EditDefaultsOnly, Category = "Abilities")
	TArray<TSubclassOf<class UGameplayEffect>> DefaultAttributeEffects;

	UPROPERTY(EditDefaultsOnly, Category = "Abilities")
	TArray<TSubclassOf<class UGameplayAbility>> DefaultAbilities;
};

