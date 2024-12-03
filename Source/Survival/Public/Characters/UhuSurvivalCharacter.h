// UhuSurvivalCharacter.h
// Copyright by MykeUhu

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "GameplayTagContainer.h"
#include "UhuSurvivalCharacter.generated.h"

class UUhuMovementDataAsset;
class UAbilitySystemComponent;
class UGameplayEffect;
class UGameplayAbility;
class UUhuSkillLevelingComponent;

UCLASS(config=Game)
class SURVIVAL_API AUhuSurvivalCharacter : public ACharacter, public IAbilitySystemInterface
{
    GENERATED_BODY()

public:
    AUhuSurvivalCharacter();

    virtual void Tick(float DeltaTime) override;
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
    virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

    UFUNCTION(BlueprintCallable, Category = "Uhu|Movement")
    void UpdateMovementSpeed(int32 SpeedLevel);

    UFUNCTION(BlueprintCallable, Category = "Uhu|Movement")
    float GetTotalDistanceWalked() const { return TotalDistanceWalked; }

    UFUNCTION(BlueprintCallable, Category = "Uhu|Movement")
    float GetTotalDistanceRun() const { return TotalDistanceRun; }

protected:
    virtual void BeginPlay() override;

    UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "GAS|Attributes")
    TSubclassOf<UGameplayEffect> DefaultVitalAttributes;
    
    UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "GAS|Attributes")
    TSubclassOf<UGameplayEffect> DefaultPrimaryAttributes;
    
    UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "GAS|Attributes")
    TSubclassOf<UGameplayEffect> DefaultSecondaryAttributes;

    UPROPERTY(EditAnywhere, Category = "Movement")
    TObjectPtr<UUhuMovementDataAsset> MovementDataAsset;
    
    void ApplyEffectToSelf(TSubclassOf<UGameplayEffect> GameplayEffectClass, float Level) const;
    virtual void InitializeDefaultAttributes() const;

private:
    UPROPERTY(EditAnywhere, Category = "GAS|Abilities")
    TArray<TSubclassOf<UGameplayAbility>> StartupAbilities;

    UPROPERTY(EditDefaultsOnly, Category = "GAS|Movement")
    TSubclassOf<UGameplayEffect> MovementSpeedEffect;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Abilities", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Skills", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UUhuSkillLevelingComponent> SkillLevelingComponent;

    int32 CurrentSpeedLevel = 4;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement", meta = (AllowPrivateAccess = "true"))
    float TotalDistanceWalked;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement", meta = (AllowPrivateAccess = "true"))
    float TotalDistanceRun;

    void UpdateDistanceTraveled(float DeltaTime);
};

