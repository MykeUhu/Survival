// UhuSurvivalCharacter.cpp
// Copyright by MykeUhu

#include "Characters/UhuSurvivalCharacter.h"
#include "Data/UhuMovementDataAsset.h"
#include "GameplayEffect.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystem/UhuAbilitySystemComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "UhuGameplayTags.h"
#include "Components/UhuSkillLevelingComponent.h"

AUhuSurvivalCharacter::AUhuSurvivalCharacter()
{
    PrimaryActorTick.bCanEverTick = true;

    AbilitySystemComponent = CreateDefaultSubobject<UUhuAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
    SkillLevelingComponent = CreateDefaultSubobject<UUhuSkillLevelingComponent>(TEXT("SkillLevelingComponent"));
    
    TotalDistanceWalked = 0.0f;
    TotalDistanceRun = 0.0f;
}

void AUhuSurvivalCharacter::BeginPlay()
{
    Super::BeginPlay();
    
    InitializeDefaultAttributes();
}

void AUhuSurvivalCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    UpdateDistanceTraveled(DeltaTime);
}

void AUhuSurvivalCharacter::UpdateDistanceTraveled(float DeltaTime)
{
    if (GetVelocity().Size() > 0)
    {
        float Distance = GetVelocity().Size() * DeltaTime;
        
        if (CurrentSpeedLevel > 5)  // Speeds above level 5 are considered running
        {
            TotalDistanceRun += Distance;
            SkillLevelingComponent->UpdateSkillProgress(FUhuGameplayTags::Get().Skill_Running, Distance);
        }
        else
        {
            TotalDistanceWalked += Distance;
            SkillLevelingComponent->UpdateSkillProgress(FUhuGameplayTags::Get().Skill_Walking, Distance);
        }
    }
}

void AUhuSurvivalCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
}

UAbilitySystemComponent* AUhuSurvivalCharacter::GetAbilitySystemComponent() const
{
    return AbilitySystemComponent;
}

void AUhuSurvivalCharacter::UpdateMovementSpeed(int32 SpeedLevel)
{
    if (!MovementDataAsset || !AbilitySystemComponent) return;

    // Remove current speed tag
    if (MovementDataAsset->SpeedLevels.IsValidIndex(CurrentSpeedLevel))
    {
        AbilitySystemComponent->RemoveLooseGameplayTag(MovementDataAsset->SpeedLevels[CurrentSpeedLevel].SpeedTag);
    }

    // Update current speed level
    CurrentSpeedLevel = FMath::Clamp(SpeedLevel, 0, MovementDataAsset->SpeedLevels.Num() - 1);

    // Add new speed tag
    const FMovementSpeedLevel& NewSpeedLevel = MovementDataAsset->SpeedLevels[CurrentSpeedLevel];
    AbilitySystemComponent->AddLooseGameplayTag(NewSpeedLevel.SpeedTag);

    // Apply movement speed effect
    if (MovementSpeedEffect)
    {
        FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
        FGameplayEffectSpecHandle SpecHandle = AbilitySystemComponent->MakeOutgoingSpec(MovementSpeedEffect, 1, EffectContext);
        
        if (SpecHandle.IsValid())
        {
            SpecHandle.Data->SetSetByCallerMagnitude(FGameplayTag::RequestGameplayTag(FName("Data.Speed")), NewSpeedLevel.Speed);
            AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
        }
    }

    // Update character movement
    GetCharacterMovement()->MaxWalkSpeed = NewSpeedLevel.Speed;
}

void AUhuSurvivalCharacter::ApplyEffectToSelf(TSubclassOf<UGameplayEffect> GameplayEffectClass, float Level) const
{
    FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
    EffectContext.AddSourceObject(this);

    FGameplayEffectSpecHandle NewHandle = AbilitySystemComponent->MakeOutgoingSpec(GameplayEffectClass, Level, EffectContext);
    if (NewHandle.IsValid())
    {
        FActiveGameplayEffectHandle ActiveGEHandle = AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*NewHandle.Data.Get());
    }
}

void AUhuSurvivalCharacter::InitializeDefaultAttributes() const
{
    ApplyEffectToSelf(DefaultVitalAttributes, 1.0f);
    ApplyEffectToSelf(DefaultPrimaryAttributes, 1.0f);
    ApplyEffectToSelf(DefaultSecondaryAttributes, 1.0f);
}

