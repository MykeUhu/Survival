// UhuAttributeSet.h
// Copyright by MykeUhu

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "UhuAttributeSet.generated.h"

/*
 * BoilerPlate für neue Attribute
 * hier einfügen,
 * in UhuGameplayTags
 * dann in GE_VitalAttributes in BP die Attribute hinzufügen
 * DA_AttributeInfo
 * Broadcast Initial Values in Overlay WidgetController!
 */

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
    GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
    GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
    GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
    GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

USTRUCT()
struct FEffectProperties
{
    GENERATED_BODY()

    FEffectProperties(){}

    FGameplayEffectContextHandle EffectContextHandle;

    UPROPERTY()
    UAbilitySystemComponent* SourceASC = nullptr;

    UPROPERTY()
    AActor* SourceAvatarActor = nullptr;

    UPROPERTY()
    AController* SourceController = nullptr;

    UPROPERTY()
    ACharacter* SourceCharacter = nullptr;

    UPROPERTY()
    UAbilitySystemComponent* TargetASC = nullptr;

    UPROPERTY()
    AActor* TargetAvatarActor = nullptr;

    UPROPERTY()
    AController* TargetController = nullptr;

    UPROPERTY()
    ACharacter* TargetCharacter = nullptr;
};

template<class T>
using TStaticFuncPtr = typename TBaseStaticDelegateInstance<T, FDefaultDelegateUserPolicy>::FFuncPtr;

UCLASS()
class SURVIVAL_API UUhuAttributeSet : public UAttributeSet
{
    GENERATED_BODY()

public:
    UUhuAttributeSet();

    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

    virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
    virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;
    virtual void PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue) override;

    TMap<FGameplayTag, TStaticFuncPtr<FGameplayAttribute()>> TagsToAttributes;

    // Vital Attributes
    UPROPERTY(BlueprintReadOnly, Category = "Attributes|Vital", ReplicatedUsing = OnRep_Health)
    FGameplayAttributeData Health;
    ATTRIBUTE_ACCESSORS(UUhuAttributeSet, Health)

    UPROPERTY(BlueprintReadOnly, Category = "Attributes|Vital", ReplicatedUsing = OnRep_Hunger)
    FGameplayAttributeData Hunger;
    ATTRIBUTE_ACCESSORS(UUhuAttributeSet, Hunger)

    UPROPERTY(BlueprintReadOnly, Category = "Attributes|Vital", ReplicatedUsing = OnRep_Thirst)
    FGameplayAttributeData Thirst;
    ATTRIBUTE_ACCESSORS(UUhuAttributeSet, Thirst)

    UPROPERTY(BlueprintReadOnly, Category = "Attributes|Vital", ReplicatedUsing = OnRep_Stamina)
    FGameplayAttributeData Stamina;
    ATTRIBUTE_ACCESSORS(UUhuAttributeSet, Stamina)

    UPROPERTY(BlueprintReadOnly, Category = "Attributes|Vital", ReplicatedUsing = OnRep_Temperature)
    FGameplayAttributeData Temperature;
    ATTRIBUTE_ACCESSORS(UUhuAttributeSet, Temperature)

    // Vital Max Attributes
    UPROPERTY(BlueprintReadOnly, Category = "Attributes|VitalMax", ReplicatedUsing = OnRep_MaxHealth)
    FGameplayAttributeData MaxHealth;
    ATTRIBUTE_ACCESSORS(UUhuAttributeSet, MaxHealth)

    UPROPERTY(BlueprintReadOnly, Category = "Attributes|VitalMax", ReplicatedUsing = OnRep_MaxHunger)
    FGameplayAttributeData MaxHunger;
    ATTRIBUTE_ACCESSORS(UUhuAttributeSet, MaxHunger)

    UPROPERTY(BlueprintReadOnly, Category = "Attributes|VitalMax", ReplicatedUsing = OnRep_MaxThirst)
    FGameplayAttributeData MaxThirst;
    ATTRIBUTE_ACCESSORS(UUhuAttributeSet, MaxThirst)

    UPROPERTY(BlueprintReadOnly, Category = "Attributes|VitalMax", ReplicatedUsing = OnRep_MaxStamina)
    FGameplayAttributeData MaxStamina;
    ATTRIBUTE_ACCESSORS(UUhuAttributeSet, MaxStamina)

    // Primary Attributes
    UPROPERTY(BlueprintReadOnly, Category = "Attributes|Primary", ReplicatedUsing = OnRep_Endurance)
    FGameplayAttributeData Endurance;
    ATTRIBUTE_ACCESSORS(UUhuAttributeSet, Endurance)

    UPROPERTY(BlueprintReadOnly, Category = "Attributes|Primary", ReplicatedUsing = OnRep_Strength)
    FGameplayAttributeData Strength;
    ATTRIBUTE_ACCESSORS(UUhuAttributeSet, Strength)

    UPROPERTY(BlueprintReadOnly, Category = "Attributes|Primary", ReplicatedUsing = OnRep_Agility)
    FGameplayAttributeData Agility;
    ATTRIBUTE_ACCESSORS(UUhuAttributeSet, Agility)

    UPROPERTY(BlueprintReadOnly, Category = "Attributes|Primary", ReplicatedUsing = OnRep_Intelligence)
    FGameplayAttributeData Intelligence;
    ATTRIBUTE_ACCESSORS(UUhuAttributeSet, Intelligence)

    // Secondary Attributes
    UPROPERTY(BlueprintReadOnly, Category = "Attributes|Secondary", ReplicatedUsing = OnRep_Cleverness)
    FGameplayAttributeData Cleverness;
    ATTRIBUTE_ACCESSORS(UUhuAttributeSet, Cleverness)

    UPROPERTY(BlueprintReadOnly, Category = "Attributes|Secondary", ReplicatedUsing = OnRep_Cleanliness)
    FGameplayAttributeData Cleanliness;
    ATTRIBUTE_ACCESSORS(UUhuAttributeSet, Cleanliness)

    UPROPERTY(BlueprintReadOnly, Category = "Attributes|Secondary", ReplicatedUsing = OnRep_Perception)
    FGameplayAttributeData Perception;
    ATTRIBUTE_ACCESSORS(UUhuAttributeSet, Perception)

    UPROPERTY(BlueprintReadOnly, Category = "Attributes|Secondary", ReplicatedUsing = OnRep_Communication)
    FGameplayAttributeData Communication;
    ATTRIBUTE_ACCESSORS(UUhuAttributeSet, Communication)

    UPROPERTY(BlueprintReadOnly, Category = "Attributes|Secondary", ReplicatedUsing = OnRep_Survivability)
    FGameplayAttributeData Survivability;
    ATTRIBUTE_ACCESSORS(UUhuAttributeSet, Survivability)

    UPROPERTY(BlueprintReadOnly, Category = "Attributes|Secondary", ReplicatedUsing = OnRep_Engineering)
    FGameplayAttributeData Engineering;
    ATTRIBUTE_ACCESSORS(UUhuAttributeSet, Engineering)

    UPROPERTY(BlueprintReadOnly, Category = "Attributes|Secondary", ReplicatedUsing = OnRep_Botany)
    FGameplayAttributeData Botany;
    ATTRIBUTE_ACCESSORS(UUhuAttributeSet, Botany)

    UPROPERTY(BlueprintReadOnly, Category = "Attributes|Secondary", ReplicatedUsing = OnRep_Technology)
    FGameplayAttributeData Technology;
    ATTRIBUTE_ACCESSORS(UUhuAttributeSet, Technology)

    // Resistances
    UPROPERTY(BlueprintReadOnly, Category = "Resistances|Temperature", ReplicatedUsing = OnRep_ResTemperature)   
    FGameplayAttributeData ResTemperature;
    ATTRIBUTE_ACCESSORS(UUhuAttributeSet, ResTemperature)

    // Vital Attributes
    UFUNCTION()
    virtual void OnRep_Health(const FGameplayAttributeData& OldHealth) const;

    UFUNCTION()
    virtual void OnRep_Hunger(const FGameplayAttributeData& OldHunger) const;

    UFUNCTION()
    virtual void OnRep_Thirst(const FGameplayAttributeData& OldThirst) const;

    UFUNCTION()
    virtual void OnRep_Stamina(const FGameplayAttributeData& OldStamina) const;

    UFUNCTION()
    virtual void OnRep_Temperature(const FGameplayAttributeData& OldTemperature) const;

    // Vital Max Attributes
    UFUNCTION()
    virtual void OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const;

    UFUNCTION()
    virtual void OnRep_MaxHunger(const FGameplayAttributeData& OldMaxHunger) const;

    UFUNCTION()
    virtual void OnRep_MaxThirst(const FGameplayAttributeData& OldMaxThirst) const;

    UFUNCTION()
    virtual void OnRep_MaxStamina(const FGameplayAttributeData& OldMaxStamina) const;

    // Primary Attributes
    UFUNCTION()
    virtual void OnRep_Endurance(const FGameplayAttributeData& OldEndurance) const;

    UFUNCTION()
    virtual void OnRep_Strength(const FGameplayAttributeData& OldStrength) const;

    UFUNCTION()
    virtual void OnRep_Agility(const FGameplayAttributeData& OldAgility) const;
    
    UFUNCTION()
    virtual void OnRep_Intelligence(const FGameplayAttributeData& OldIntelligence) const;

    // Secondary Attributes
    UFUNCTION()
    void OnRep_Cleverness(const FGameplayAttributeData& OldCleverness) const;

    UFUNCTION()
    void OnRep_Cleanliness(const FGameplayAttributeData& OldCleanliness) const;

    UFUNCTION()
    void OnRep_Perception(const FGameplayAttributeData& OldPerception) const;

    UFUNCTION()
    void OnRep_Communication(const FGameplayAttributeData& OldCommunication) const;

    UFUNCTION()
    void OnRep_Survivability(const FGameplayAttributeData& OldSurvivability) const;

    UFUNCTION()
    void OnRep_Engineering(const FGameplayAttributeData& OldEngineering) const;

    UFUNCTION()
    void OnRep_Botany(const FGameplayAttributeData& OldBotany) const;

    UFUNCTION()
    void OnRep_Technology(const FGameplayAttributeData& OldTechnology) const;

    // Resistances
    UFUNCTION()
    void OnRep_ResTemperature(const FGameplayAttributeData& OldResTemperature) const;
    
private:
    void SetEffectProperties(const FGameplayEffectModCallbackData& Data, FEffectProperties& Props) const;
    bool bTopOffHealth = false;
    bool bTopOffHunger = false;
    bool bTopOffThirst = false;
    bool bTopOffStamina = false;
};

