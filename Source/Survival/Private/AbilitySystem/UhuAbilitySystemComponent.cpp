// UhuAbilitySystemComponent.cpp
// Copyright by MykeUhu

#include "AbilitySystem/UhuAbilitySystemComponent.h"

#include "UhuGameplayTags.h"
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

void UUhuAbilitySystemComponent::AddCharacterAbilities(const TArray<TSubclassOf<UGameplayAbility>>& StartupAbilities)
{
	for (const TSubclassOf<UGameplayAbility> AbilityClass : StartupAbilities)
	{
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(AbilityClass, 1);
		if (const UUhuGameplayAbility* UhuAbility = Cast<UUhuGameplayAbility>(AbilitySpec.Ability))
		{
			AbilitySpec.DynamicAbilityTags.AddTag(UhuAbility->StartupInputTag);
			AbilitySpec.DynamicAbilityTags.AddTag(FUhuGameplayTags::Get().Abilities_Status_Equipped);
			GiveAbility(AbilitySpec);
		}
	}
	bStartupAbilitiesGiven = true;
	AbilitiesGivenDelegate.Broadcast();
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

void UUhuAbilitySystemComponent::ForEachAbility(const FForEachAbility& Delegate)
{
	FScopedAbilityListLock ActiveScopeLock(*this);
	for (const FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		if (!Delegate.ExecuteIfBound(AbilitySpec))
		{
			UE_LOG(LogTemp, Error, TEXT("Failed to execute delegate in %hs"), __FUNCTION__);
		}
	}
}

FGameplayTag UUhuAbilitySystemComponent::GetAbilityTagFromSpec(const FGameplayAbilitySpec& AbilitySpec)
{
	if (AbilitySpec.Ability)
	{
		for (FGameplayTag Tag : AbilitySpec.Ability.Get()->AbilityTags)
		{
			if (Tag.MatchesTag(FGameplayTag::RequestGameplayTag(FName("Abilities"))))
			{
				return Tag;
			}
		}
	}
	return FGameplayTag();
}
