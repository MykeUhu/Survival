// OverlayWidgetController.cpp
// Copyright by MykeUhu

#include "UI/WidgetController/OverlayWidgetController.h"

#include "UhuGameplayTags.h"
#include "AbilitySystem/UhuAbilitySystemComponent.h"
#include "AbilitySystem/UhuAttributeSet.h"
#include "AbilitySystem/Data/AbilityInfo.h"
//#include "AbilitySystem/Data/LevelUpInfo.h"
#include "Player/UhuPlayerState.h"

void UOverlayWidgetController::BroadcastInitialValues()
{

	OnHealthChanged.Broadcast(GetUhuAS()->GetHealth());
	OnHungerChanged.Broadcast(GetUhuAS()->GetHunger());
	OnThirstChanged.Broadcast(GetUhuAS()->GetThirst());
	OnStaminaChanged.Broadcast(GetUhuAS()->GetStamina());
	OnTemperatureChanged.Broadcast(GetUhuAS()->GetTemperature());

	OnMaxHealthChanged.Broadcast(GetUhuAS()->GetMaxHealth());
	OnMaxHungerChanged.Broadcast(GetUhuAS()->GetMaxHunger());
	OnMaxThirstChanged.Broadcast(GetUhuAS()->GetMaxThirst());
	OnMaxStaminaChanged.Broadcast(GetUhuAS()->GetMaxStamina());
}

void UOverlayWidgetController::BindCallbacksToDependencies()
{
    // Binde die Attribute-Änderungs-Delegaten
    AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(GetUhuAS()->GetHealthAttribute()).AddLambda(
        [this](const FOnAttributeChangeData& Data)
        {
            OnHealthChanged.Broadcast(Data.NewValue);
        }
    );

    AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(GetUhuAS()->GetHungerAttribute()).AddLambda(
        [this](const FOnAttributeChangeData& Data)
        {
            OnHungerChanged.Broadcast(Data.NewValue);
        }
    );

    AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(GetUhuAS()->GetThirstAttribute()).AddLambda(
        [this](const FOnAttributeChangeData& Data)
        {
            OnThirstChanged.Broadcast(Data.NewValue);
        }
    );

    AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(GetUhuAS()->GetStaminaAttribute()).AddLambda(
        [this](const FOnAttributeChangeData& Data)
        {
            OnStaminaChanged.Broadcast(Data.NewValue);
        }
    );

    AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(GetUhuAS()->GetTemperatureAttribute()).AddLambda(
        [this](const FOnAttributeChangeData& Data)
        {
            OnTemperatureChanged.Broadcast(Data.NewValue);
        }
    );

    AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(GetUhuAS()->GetMaxHealthAttribute()).AddLambda(
        [this](const FOnAttributeChangeData& Data)
        {
            OnMaxHealthChanged.Broadcast(Data.NewValue);
        }
    );

    AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(GetUhuAS()->GetMaxHungerAttribute()).AddLambda(
        [this](const FOnAttributeChangeData& Data)
        {
            OnMaxHungerChanged.Broadcast(Data.NewValue);
        }
    );

    AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(GetUhuAS()->GetMaxThirstAttribute()).AddLambda(
        [this](const FOnAttributeChangeData& Data)
        {
            OnMaxThirstChanged.Broadcast(Data.NewValue);
        }
    );

    AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(GetUhuAS()->GetMaxStaminaAttribute()).AddLambda(
        [this](const FOnAttributeChangeData& Data)
        {
            OnMaxStaminaChanged.Broadcast(Data.NewValue);
        }
    );
    
    if (GetUhuASC())
    {
        GetUhuASC()->AbilityEquipped.AddUObject(this, &UOverlayWidgetController::OnAbilityEquipped);
        if (GetUhuASC()->bStartupAbilitiesGiven)
        {
            BroadcastAbilityInfo();
        }
        else
        {
            GetUhuASC()->AbilitiesGivenDelegate.AddUObject(this, &UOverlayWidgetController::BroadcastAbilityInfo);
        }
    }
}

void UOverlayWidgetController::OnAbilityEquipped(const FGameplayTag& AbilityTag, const FGameplayTag& Status, const FGameplayTag& Slot, const FGameplayTag& PreviousSlot) const
{
    const FUhuGameplayTags& GameplayTags = FUhuGameplayTags::Get();
	
    FUhuAbilityInfo LastSlotInfo;
    LastSlotInfo.StatusTag = GameplayTags.Abilities_Status_Unlocked;
    LastSlotInfo.InputTag = PreviousSlot;
    LastSlotInfo.AbilityTag = GameplayTags.Abilities_None;
    // Broadcast empty info if PreviousSlot is a valid slot. Only if equipping an already-equipped spell
    AbilityInfoDelegate.Broadcast(LastSlotInfo);

    FUhuAbilityInfo Info = AbilityInfo->FindAbilityInfoForTag(AbilityTag);
    Info.StatusTag = Status;
    Info.InputTag = Slot;
    AbilityInfoDelegate.Broadcast(Info);
}