// UhuAbilitySystemComponent.cpp
// Copyright by MykeUhu

#include "AbilitySystem/UhuAbilitySystemComponent.h"
#include "AbilitySystem/UhuGameplayAbility.h"

UUhuAbilitySystemComponent::UUhuAbilitySystemComponent()
{
}

void UUhuAbilitySystemComponent::InitializeComponent()
{
	Super::InitializeComponent();

	InitializeAttributes();
	GiveStartupAbilities();
}

void UUhuAbilitySystemComponent::InitializeAttributes()
{
	for (TSubclassOf<UGameplayEffect>& AttributeEffect : DefaultAttributeEffects)
	{
		FGameplayEffectContextHandle EffectContext = MakeEffectContext();
		EffectContext.AddSourceObject(this);

		FGameplayEffectSpecHandle NewHandle = MakeOutgoingSpec(AttributeEffect, 1, EffectContext);
		if (NewHandle.IsValid())
		{
			ApplyGameplayEffectSpecToSelf(*NewHandle.Data.Get());
		}
	}
}

void UUhuAbilitySystemComponent::GiveStartupAbilities()
{
	for (TSubclassOf<UGameplayAbility>& Ability : DefaultAbilities)
	{
		GiveAbility(FGameplayAbilitySpec(Ability, 1, INDEX_NONE, this));
	}
}

void UUhuAbilitySystemComponent::ServerApplyAttributePoint_Implementation(FGameplayAttribute Attribute, float Value)
{
	FGameplayEffectContextHandle EffectContext = MakeEffectContext();
	EffectContext.AddSourceObject(this);

	FGameplayEffectSpecHandle SpecHandle = MakeOutgoingSpec(UGameplayEffect::StaticClass(), 1, EffectContext);
	if (SpecHandle.IsValid())
	{
		SpecHandle.Data->SetSetByCallerMagnitude(Attribute.GetUProperty()->GetFName(), Value);
		ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
	}
}

bool UUhuAbilitySystemComponent::ServerApplyAttributePoint_Validate(FGameplayAttribute Attribute, float Value)
{
	// Add validation logic here if needed
	return true;
}

