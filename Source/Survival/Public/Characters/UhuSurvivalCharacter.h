// UhuSurvivalCharacter.h
// Copyright by MykeUhu

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "GameplayTagContainer.h"
#include "Components/DistanceProgressionComponent.h"
#include "UhuGameplayTags.h"
#include "AbilitySystem/Data/CharacterClassInfo.h"
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
    float GetTotalDistanceWalkedKM() const;

    UFUNCTION(BlueprintCallable, Category = "Uhu|Movement")
    float GetTotalDistanceRunKM() const;

    UFUNCTION(BlueprintCallable, Category = "Uhu|Movement")
    void SetMovementSpeedTag(FGameplayTag NewSpeedTag);

    void ApplyMovementSpeed(float Speed);

    void CharacterMove(const FVector2D& MoveDirection);

    UFUNCTION(BlueprintCallable, Category = "Uhu|Movement")
    void AdjustMovementSpeed(int32 Delta);

    UFUNCTION(BlueprintCallable, Category = "Uhu|Movement")
    void RestorePreviousMovementSpeed();

    UFUNCTION(BlueprintCallable, Category = "Uhu|Movement")
    FGameplayTag GetCurrentSpeedTag() const { return CurrentSpeedTag; }

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Class Defaults")
    ECharacterClass CharacterClass = ECharacterClass::Player;

protected:
    virtual void BeginPlay() override;

    UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "GAS|Attributes")
    TSubclassOf<UGameplayEffect> DefaultVitalAttributes;
    
    UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "GAS|Attributes")
    TSubclassOf<UGameplayEffect> DefaultPrimaryAttributes;
    
    UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "GAS|Attributes")
    TSubclassOf<UGameplayEffect> DefaultSecondaryAttributes;

    UPROPERTY(BlueprintReadWrite, Category = "Movement")
    FGameplayTag CurrentSpeedTag;
    
    UPROPERTY(EditAnywhere, Category = "Movement")
    TObjectPtr<UUhuMovementDataAsset> MovementDataAsset;
    
    void ApplyEffectToSelf(TSubclassOf<UGameplayEffect> GameplayEffectClass, float Level) const;
    virtual void InitializeDefaultAttributes() const;

private:
    UPROPERTY(EditAnywhere, Category = "GAS|Abilities")
    TArray<TSubclassOf<UGameplayAbility>> StartupAbilities;

    UPROPERTY(EditDefaultsOnly, Category = "GAS|Movement")
    TSubclassOf<UGameplayEffect> MovementSpeedEffect;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GAS|Abilities", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GAS|Skills", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UUhuSkillLevelingComponent> SkillLevelingComponent;

    int32 CurrentSpeedLevel = 4;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GAS|Movement", meta = (AllowPrivateAccess = "true"))
    float TotalDistanceWalked;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GAS|Movement", meta = (AllowPrivateAccess = "true"))
    float TotalDistanceRun;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GAS|Leveling", meta = (AllowPrivateAccess = "true"))
    UDistanceProgressionComponent* DistanceProgressionComponent;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GAS|Leveling", meta = (AllowPrivateAccess = "true"))
    UDataTable* MilestoneTable;

    UFUNCTION()
    void OnMilestoneReached();

    FGameplayTag OldSpeedTag;

    UPROPERTY()
    FGameplayTag PreviousSpeedTag;

    bool IsWalking() const;
    bool IsRunning() const;
    
    void UpdateDistanceTraveled(float DeltaTime);
    void RemoveAllMovementSpeedTags();
    void ApplyMovementSpeedTag(FGameplayTag SpeedTag);
};

