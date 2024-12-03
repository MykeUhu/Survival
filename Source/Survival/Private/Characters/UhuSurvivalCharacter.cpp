// UhuSurvivalCharacter.cpp
// Copyright by MykeUhu

#include "Characters/UhuSurvivalCharacter.h"
#include "Data/UhuMovementDataAsset.h"
#include "GameplayEffect.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystem/UhuAbilitySystemComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AUhuSurvivalCharacter::AUhuSurvivalCharacter()
{
    // Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    // Initialize AbilitySystemComponent
    AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
}

// Called when the game starts or when spawned
void AUhuSurvivalCharacter::BeginPlay()
{
    Super::BeginPlay();
}

void AUhuSurvivalCharacter::ApplyEffectToSelf(TSubclassOf<UGameplayEffect> GameplayEffectClass, float Level) const
{
    check(IsValid(GetAbilitySystemComponent()));
    check(GameplayEffectClass);
    FGameplayEffectContextHandle ContextHandle = GetAbilitySystemComponent()->MakeEffectContext();
    ContextHandle.AddSourceObject(this);
    const FGameplayEffectSpecHandle SpecHandle = GetAbilitySystemComponent()->MakeOutgoingSpec(GameplayEffectClass, Level, ContextHandle);
    GetAbilitySystemComponent()->ApplyGameplayEffectSpecToTarget(*SpecHandle.Data.Get(), GetAbilitySystemComponent());
}

void AUhuSurvivalCharacter::InitializeDefaultAttributes() const
{
    ApplyEffectToSelf(DefaultVitalAttributes, 1.f);
    ApplyEffectToSelf(DefaultPrimaryAttributes, 1.f);
    ApplyEffectToSelf(DefaultSecondaryAttributes, 1.f);
   
}

// Called every frame
void AUhuSurvivalCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AUhuSurvivalCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
}

// Implement IAbilitySystemInterface
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
