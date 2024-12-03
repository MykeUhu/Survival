// UhuAttributeSet.cpp
// Copyright by MykeUhu

#include "AbilitySystem/UhuAttributeSet.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "GameFramework/Character.h"
#include "GameplayEffectExtension.h"
#include "Net/UnrealNetwork.h"
#include "UhuGameplayTags.h"
#include "Net/UnrealNetwork.h"

UUhuAttributeSet::UUhuAttributeSet()
{
    const FUhuGameplayTags& GameplayTags = FUhuGameplayTags::Get();
    
    /*
    * Vital Attributes
    */
    TagsToAttributes.Add(GameplayTags.Attribute_Vital_Health, GetHealthAttribute);
    TagsToAttributes.Add(GameplayTags.Attribute_Vital_Hunger, GetHungerAttribute);
    TagsToAttributes.Add(GameplayTags.Attribute_Vital_Thirst, GetThirstAttribute);
    TagsToAttributes.Add(GameplayTags.Attribute_Vital_Stamina, GetStaminaAttribute);
    TagsToAttributes.Add(GameplayTags.Attribute_Vital_Temperature, GetTemperatureAttribute);

    /*
    * Vital Max Attributes
    */
    TagsToAttributes.Add(GameplayTags.Attribute_Vital_MaxHealth, GetMaxHealthAttribute);
    TagsToAttributes.Add(GameplayTags.Attribute_Vital_MaxHunger, GetMaxHungerAttribute);
    TagsToAttributes.Add(GameplayTags.Attribute_Vital_MaxThirst, GetMaxThirstAttribute);
    TagsToAttributes.Add(GameplayTags.Attribute_Vital_MaxStamina, GetMaxStaminaAttribute);

    /*
    * Primnary Attribute
    */
    TagsToAttributes.Add(GameplayTags.Attribute_Primary_Endurance, GetEnduranceAttribute);
    TagsToAttributes.Add(GameplayTags.Attribute_Primary_Strength, GetStrengthAttribute);
    TagsToAttributes.Add(GameplayTags.Attribute_Primary_Agility, GetAgilityAttribute);
    TagsToAttributes.Add(GameplayTags.Attribute_Primary_Intelligence, GetIntelligenceAttribute);
	    

    /*
    * Secondary Attribute
    */
    TagsToAttributes.Add(GameplayTags.Attribute_Secondary_Cleverness, GetClevernessAttribute);
    TagsToAttributes.Add(GameplayTags.Attribute_Secondary_Cleanliness, GetCleanlinessAttribute);
    TagsToAttributes.Add(GameplayTags.Attribute_Secondary_Perception, GetPerceptionAttribute);
    TagsToAttributes.Add(GameplayTags.Attribute_Secondary_Communication, GetCommunicationAttribute);
    TagsToAttributes.Add(GameplayTags.Attribute_Secondary_Survivability, GetSurvivabilityAttribute);
    TagsToAttributes.Add(GameplayTags.Attribute_Secondary_Engineering, GetEngineeringAttribute);
    TagsToAttributes.Add(GameplayTags.Attribute_Secondary_Botany, GetBotanyAttribute);
    TagsToAttributes.Add(GameplayTags.Attribute_Secondary_Technology, GetTechnologyAttribute);
	    
    /*
    * Resistances
    */
    TagsToAttributes.Add(GameplayTags.Resistances_ResTemperature, GetResTemperatureAttribute);
        
}
void UUhuAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    const FUhuGameplayTags& GameplayTags = FUhuGameplayTags::Get();

    // Vital Attributes
    DOREPLIFETIME_CONDITION_NOTIFY(UUhuAttributeSet, Health, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UUhuAttributeSet, Hunger, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UUhuAttributeSet, Thirst, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UUhuAttributeSet, Stamina, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UUhuAttributeSet, Temperature, COND_None, REPNOTIFY_Always);

    // Vital Max Attributes
    DOREPLIFETIME_CONDITION_NOTIFY(UUhuAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UUhuAttributeSet, MaxHunger, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UUhuAttributeSet, MaxThirst, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UUhuAttributeSet, MaxStamina, COND_None, REPNOTIFY_Always);

    // Primary Attributes
    DOREPLIFETIME_CONDITION_NOTIFY(UUhuAttributeSet, Endurance, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UUhuAttributeSet, Strength, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UUhuAttributeSet, Agility, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UUhuAttributeSet, Intelligence, COND_None, REPNOTIFY_Always);

    // Secondary Attributes
    DOREPLIFETIME_CONDITION_NOTIFY(UUhuAttributeSet, Cleverness, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UUhuAttributeSet, Cleanliness, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UUhuAttributeSet, Perception, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UUhuAttributeSet, Communication, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UUhuAttributeSet, Survivability, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UUhuAttributeSet, Engineering, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UUhuAttributeSet, Botany, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UUhuAttributeSet, Technology, COND_None, REPNOTIFY_Always);
    // Resistances
    DOREPLIFETIME_CONDITION_NOTIFY(UUhuAttributeSet, ResTemperature, COND_None, REPNOTIFY_Always);
}

void UUhuAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
    Super::PreAttributeChange(Attribute, NewValue);
    if (Attribute == GetHealthAttribute())
    {
        NewValue = FMath::Clamp(NewValue, 0.0f, GetMaxHealth());
    }
    if (Attribute == GetHungerAttribute())
    {
        NewValue = FMath::Clamp(NewValue, 0.0f, GetMaxHunger());
    }
    if (Attribute == GetThirstAttribute())
    {
        NewValue = FMath::Clamp(NewValue, 0.0f, GetMaxThirst());
    }
    if (Attribute == GetStaminaAttribute())
    {
        NewValue = FMath::Clamp(NewValue, 0.0f, GetMaxStamina());
    }
}

void UUhuAttributeSet::SetEffectProperties(const FGameplayEffectModCallbackData& Data, FEffectProperties& Props) const
{
    // Source = causer of the effect, Target = target of the effect (owner of this AS)

    Props.EffectContextHandle = Data.EffectSpec.GetContext();
    Props.SourceASC = Props.EffectContextHandle.GetOriginalInstigatorAbilitySystemComponent();

    if (IsValid(Props.SourceASC) && Props.SourceASC->AbilityActorInfo.IsValid() && Props.SourceASC->AbilityActorInfo->AvatarActor.IsValid())
    {
        Props.SourceAvatarActor = Props.SourceASC->AbilityActorInfo->AvatarActor.Get();
        Props.SourceController = Props.SourceASC->AbilityActorInfo->PlayerController.Get();
        if (Props.SourceController == nullptr && Props.SourceAvatarActor != nullptr)
        {
            if (const APawn* Pawn = Cast<APawn>(Props.SourceAvatarActor))
            {
                Props.SourceController = Pawn->GetController();
            }
        }
        if (Props.SourceController)
        {
            Props.SourceCharacter = Cast<ACharacter>(Props.SourceController->GetPawn());
        }
    }

    if (Data.Target.AbilityActorInfo.IsValid() && Data.Target.AbilityActorInfo->AvatarActor.IsValid())
    {
        Props.TargetAvatarActor = Data.Target.AbilityActorInfo->AvatarActor.Get();
        Props.TargetController = Data.Target.AbilityActorInfo->PlayerController.Get();
        Props.TargetCharacter = Cast<ACharacter>(Props.TargetAvatarActor);
        Props.TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Props.TargetAvatarActor);
    }
}

void UUhuAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
    Super::PostGameplayEffectExecute(Data);

    FEffectProperties Props;
    SetEffectProperties(Data, Props);
    if (Data.EvaluatedData.Attribute == GetHealthAttribute())
    {
        SetHealth(FMath::Clamp(GetHealth(), 0.f, GetMaxHealth()));
    }
    if (Data.EvaluatedData.Attribute == GetHungerAttribute())
    {
        SetHunger(FMath::Clamp(GetHunger(), 0.f, GetMaxHunger()));
    }
    if (Data.EvaluatedData.Attribute == GetThirstAttribute())
    {
        SetThirst(FMath::Clamp(GetThirst(), 0.f, GetMaxThirst()));
    }

    if (Data.EvaluatedData.Attribute == GetStaminaAttribute())
    {
        SetStamina(FMath::Clamp(GetStamina(), 0.f, GetMaxStamina()));
    }
}

void UUhuAttributeSet::PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue)
{
    Super::PostAttributeChange(Attribute, OldValue, NewValue);
    
    if (Attribute == GetMaxHealthAttribute() && bTopOffHealth)
    {
        SetHealth(GetMaxHealth());
        bTopOffHealth = false;
    }
    if (Attribute == GetMaxHungerAttribute() && bTopOffHunger)
    {
        SetHunger(GetMaxHunger());
        bTopOffHunger = false;
    }
    if (Attribute == GetMaxThirstAttribute() && bTopOffThirst)
    {
        SetThirst(GetMaxThirst());
        bTopOffThirst = false;
    }
    if (Attribute == GetMaxStaminaAttribute() && bTopOffStamina)
    {
        SetStamina(GetMaxStamina());
        bTopOffStamina = false;
    }
}

// Vital Attributes
void UUhuAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth) const
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UUhuAttributeSet, Health, OldHealth);
}

void UUhuAttributeSet::OnRep_Hunger(const FGameplayAttributeData& OldHunger) const
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UUhuAttributeSet, Hunger, OldHunger);
}

void UUhuAttributeSet::OnRep_Thirst(const FGameplayAttributeData& OldThirst) const
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UUhuAttributeSet, Thirst, OldThirst);
}

void UUhuAttributeSet::OnRep_Stamina(const FGameplayAttributeData& OldStamina) const
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UUhuAttributeSet, Stamina, OldStamina);
}

void UUhuAttributeSet::OnRep_Temperature(const FGameplayAttributeData& OldTemperature) const
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UUhuAttributeSet, Temperature, OldTemperature);
}

// Vital Max Attributes
void UUhuAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UUhuAttributeSet, MaxHealth, OldMaxHealth);
}

void UUhuAttributeSet::OnRep_MaxHunger(const FGameplayAttributeData& OldMaxHunger) const
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UUhuAttributeSet, MaxHunger, OldMaxHunger);
}

void UUhuAttributeSet::OnRep_MaxThirst(const FGameplayAttributeData& OldMaxThirst) const
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UUhuAttributeSet, MaxThirst, OldMaxThirst);
}

void UUhuAttributeSet::OnRep_MaxStamina(const FGameplayAttributeData& OldMaxStamina) const
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UUhuAttributeSet, MaxStamina, OldMaxStamina);
}

// Primary Attributes
void UUhuAttributeSet::OnRep_Endurance(const FGameplayAttributeData& OldEndurance) const
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UUhuAttributeSet, Endurance, OldEndurance);
}

void UUhuAttributeSet::OnRep_Strength(const FGameplayAttributeData& OldStrength) const
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UUhuAttributeSet, Strength, OldStrength);
}

void UUhuAttributeSet::OnRep_Agility(const FGameplayAttributeData& OldAgility) const
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UUhuAttributeSet, Agility, OldAgility);
}

void UUhuAttributeSet::OnRep_Intelligence(const FGameplayAttributeData& OldIntelligence) const
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UUhuAttributeSet, Intelligence, OldIntelligence);
}

// Secondary Attributes
void UUhuAttributeSet::OnRep_Cleverness(const FGameplayAttributeData& OldCleverness) const
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UUhuAttributeSet, Cleverness, OldCleverness);
}

void UUhuAttributeSet::OnRep_Cleanliness(const FGameplayAttributeData& OldCleanliness) const
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UUhuAttributeSet, Cleanliness, OldCleanliness);
}

void UUhuAttributeSet::OnRep_Perception(const FGameplayAttributeData& OldPerception) const
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UUhuAttributeSet, Perception, OldPerception);
}

void UUhuAttributeSet::OnRep_Communication(const FGameplayAttributeData& OldCommunication) const
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UUhuAttributeSet, Communication, OldCommunication);
}

void UUhuAttributeSet::OnRep_Survivability(const FGameplayAttributeData& OldSurvivability) const
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UUhuAttributeSet, Survivability, OldSurvivability);
}

void UUhuAttributeSet::OnRep_Engineering(const FGameplayAttributeData& OldEngineering) const
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UUhuAttributeSet, Engineering, OldEngineering);
}

void UUhuAttributeSet::OnRep_Botany(const FGameplayAttributeData& OldBotany) const
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UUhuAttributeSet, Botany, OldBotany);
}

void UUhuAttributeSet::OnRep_Technology(const FGameplayAttributeData& OldTechnology) const
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UUhuAttributeSet, Technology, OldTechnology);
}

// Resistances
void UUhuAttributeSet::OnRep_ResTemperature(const FGameplayAttributeData& OldResTemperature) const
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UUhuAttributeSet, ResTemperature, OldResTemperature);
}

