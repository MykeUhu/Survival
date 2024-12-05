// UhuSurvivalCharacter.h
// Copyright by MykeUhu

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "UhuGameplayTags.h"
#include "AbilitySystem/Data/CharacterClassInfo.h"
#include "Interaction/PlayerInterface.h"
#include "UhuSurvivalCharacter.generated.h"

class UUhuAbilitySystemComponent;
class UUhuAttributeSet;
class UUhuSkillLevelingComponent;
class UDistanceProgressionComponent;
class UUhuMovementDataAsset;
class UGameplayEffect;
class UGameplayAbility;
class UDataTable;

UCLASS(config=Game)
class SURVIVAL_API AUhuSurvivalCharacter : public ACharacter, public IAbilitySystemInterface, public IPlayerInterface
{
    GENERATED_BODY()
public:
    AUhuSurvivalCharacter();

    virtual void PossessedBy(AController* NewController) override;
    virtual void OnRep_PlayerState() override;
    virtual void Tick(float DeltaTime) override;
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
    UUhuAttributeSet* GetAttributeSet() const { return AttributeSet; }
    
    virtual ECharacterClass GetCharacterClass_Implementation();

    UFUNCTION(BlueprintCallable, Category = "Uhu|Movement")
    void SetMovementSpeedTag(FGameplayTag NewSpeedTag);

    UFUNCTION(BlueprintCallable, Category = "Uhu|Movement")
    float GetTotalDistanceWalkedKM() const;

    UFUNCTION(BlueprintCallable, Category = "Uhu|Movement")
    float GetTotalDistanceRunKM() const;

    UFUNCTION(BlueprintCallable, Category = "Uhu|Movement")
    void CharacterMove(const FVector2D& MoveDirection);

    UFUNCTION(BlueprintCallable, Category = "Uhu|Movement")
    void AdjustMovementSpeed(int32 Delta);

    UFUNCTION(BlueprintCallable, Category = "Uhu|Movement")
    void RestorePreviousMovementSpeed();

    UFUNCTION(BlueprintCallable, Category = "Uhu|Movement")
    FGameplayTag GetCurrentSpeedTag() const { return CurrentSpeedTag; }

protected:
    virtual void BeginPlay() override;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Abilities")
    UUhuAbilitySystemComponent* AbilitySystemComponent;

    UPROPERTY()
    UUhuAttributeSet* AttributeSet;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UUhuSkillLevelingComponent* SkillLevelingComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UDistanceProgressionComponent* DistanceProgressionComponent;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement")
    UUhuMovementDataAsset* MovementDataAsset;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Leveling")
    UDataTable* MilestoneTable;

    UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "GAS|Attributes")
    TSubclassOf<UGameplayEffect> DefaultVitalAttributes;
    
    UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "GAS|Attributes")
    TSubclassOf<UGameplayEffect> DefaultPrimaryAttributes;
    
    UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "GAS|Attributes")
    TSubclassOf<UGameplayEffect> DefaultSecondaryAttributes;

    // Replizierbare Variable für Bewegungsgeschwindigkeit
    UPROPERTY(ReplicatedUsing = OnRep_MovementSpeed)
    float MaxWalkSpeed;

    // Funktion, die bei Änderungen der MaxWalkSpeed ausgeführt wird
    UFUNCTION()
    void OnRep_MovementSpeed();
    
    UPROPERTY(BlueprintReadWrite, Category = "Movement")
    FGameplayTag CurrentSpeedTag;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Class Defaults")
    ECharacterClass CharacterClass = ECharacterClass::Player;

    UFUNCTION()
    void OnMilestoneReached();

private:
    void InitializeAttributes();
    void GiveDefaultAbilities();
    void ApplyEffectToSelf(TSubclassOf<UGameplayEffect> GameplayEffectClass, float Level) const;
    void ApplyMovementSpeed(float Speed);
    void RemoveAllMovementSpeedTags();
    void ApplyMovementSpeedTag(FGameplayTag SpeedTag);
    void UpdateDistanceTraveled(float DeltaTime);
    bool IsWalking() const;
    bool IsRunning() const;

    UPROPERTY(EditAnywhere, Category = "GAS|Abilities")
    TArray<TSubclassOf<UGameplayAbility>> StartupAbilities;

    UPROPERTY(EditDefaultsOnly, Category = "GAS|Movement")
    TSubclassOf<UGameplayEffect> MovementSpeedEffect;

    int32 CurrentSpeedLevel;
    float TotalDistanceWalked;
    float TotalDistanceRun;
    FGameplayTag PreviousSpeedTag;
};