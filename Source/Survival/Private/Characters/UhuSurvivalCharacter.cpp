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

float AUhuSurvivalCharacter::GetTotalDistanceWalkedKM() const
{
    return FMath::RoundToFloat((TotalDistanceWalked / 100000.0f) * 10.0f) / 10.0f;
}

float AUhuSurvivalCharacter::GetTotalDistanceRunKM() const
{
    return FMath::RoundToFloat((TotalDistanceRun / 100000.0f) * 10.0f) / 10.0f;
}

void AUhuSurvivalCharacter::SetMovementSpeedTag(FGameplayTag NewSpeedTag)
{
    if (!MovementDataAsset || !NewSpeedTag.IsValid())
    {
        UE_LOG(LogTemp, Warning, TEXT("Invalid Movement Data Asset or Speed Tag!"));
        return;
    }

    RemoveAllMovementSpeedTags();
    ApplyMovementSpeedTag(NewSpeedTag);

    // Set the character's speed
    const FMovementSpeedLevel SpeedLevel = MovementDataAsset->GetSpeedLevelForTag(NewSpeedTag);
    if (SpeedLevel.Speed >= 0.f)
    {
        ApplyMovementSpeed(SpeedLevel.Speed);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Invalid Speed Level for Tag: %s"), *NewSpeedTag.ToString());
    }

    UE_LOG(LogTemp, Display, TEXT("Current Speed Tag: %s"), *CurrentSpeedTag.ToString());
    UE_LOG(LogTemp, Display, TEXT("Previous Speed Tag: %s"), *PreviousSpeedTag.ToString());
}

void AUhuSurvivalCharacter::ApplyMovementSpeed(float Speed)
{
    if (GetCharacterMovement())
    {
        GetCharacterMovement()->MaxWalkSpeed = Speed;
    }
}

void AUhuSurvivalCharacter::CharacterMove(const FVector2D& MoveDirection)
{
    if (Controller)
    {
        // Forward movement (X-axis)
        if (MoveDirection.X != 0.0f)
        {
            const FRotator Rotation = Controller->GetControlRotation();
            const FRotator YawRotation(0, Rotation.Yaw, 0);
            const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

            AddMovementInput(ForwardDirection, MoveDirection.X);
        }

        // Sideways movement (Y-axis)
        if (MoveDirection.Y != 0.0f)
        {
            const FRotator Rotation = Controller->GetControlRotation();
            const FRotator YawRotation(0, Rotation.Yaw, 0);
            const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

            AddMovementInput(RightDirection, MoveDirection.Y);
        }
    }
}

void AUhuSurvivalCharacter::BeginPlay()
{
    Super::BeginPlay();
    
    InitializeDefaultAttributes();
    if (MovementDataAsset && MovementDataAsset->DefaultSpeedTag.IsValid())
    {
        SetMovementSpeedTag(MovementDataAsset->DefaultSpeedTag);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("No Default Speed Tag defined in Movement Data Asset!"));
    }

    OldSpeedTag = CurrentSpeedTag;
}

void AUhuSurvivalCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    UpdateDistanceTraveled(DeltaTime);
}

bool AUhuSurvivalCharacter::IsWalking() const
{
    return CurrentSpeedTag.MatchesTag(FUhuGameplayTags::Get().Movement_Speed_1) ||
           CurrentSpeedTag.MatchesTag(FUhuGameplayTags::Get().Movement_Speed_2) ||
           CurrentSpeedTag.MatchesTag(FUhuGameplayTags::Get().Movement_Speed_3) ||
           CurrentSpeedTag.MatchesTag(FUhuGameplayTags::Get().Movement_Speed_4) ||
           CurrentSpeedTag.MatchesTag(FUhuGameplayTags::Get().Movement_Speed_5);
}

bool AUhuSurvivalCharacter::IsRunning() const
{
    return CurrentSpeedTag.MatchesTag(FUhuGameplayTags::Get().Movement_Speed_6) ||
           CurrentSpeedTag.MatchesTag(FUhuGameplayTags::Get().Movement_Speed_7) ||
           CurrentSpeedTag.MatchesTag(FUhuGameplayTags::Get().Movement_Speed_8) ||
           CurrentSpeedTag.MatchesTag(FUhuGameplayTags::Get().Movement_Speed_9) ||
           CurrentSpeedTag.MatchesTag(FUhuGameplayTags::Get().Movement_Speed_10);
}

void AUhuSurvivalCharacter::UpdateDistanceTraveled(float DeltaTime)
{
    float VelocityMagnitude = GetVelocity().Size();

    // If the character is not moving
    if (VelocityMagnitude <= KINDA_SMALL_NUMBER)
    {
        if (CurrentSpeedTag != FUhuGameplayTags::Get().Movement_Speed_0)
        {
            SetMovementSpeedTag(FUhuGameplayTags::Get().Movement_Speed_0);
            UE_LOG(LogTemp, Display, TEXT("Character is now idle."));
        }
        return;
    }

    // Distance calculation
    float Distance = VelocityMagnitude * DeltaTime;

    if (IsWalking())
    {
        TotalDistanceWalked += Distance;
        SkillLevelingComponent->UpdateSkillProgress(FUhuGameplayTags::Get().Skill_Walking, Distance);
    }
    else if (IsRunning())
    {
        TotalDistanceRun += Distance;
        SkillLevelingComponent->UpdateSkillProgress(FUhuGameplayTags::Get().Skill_Running, Distance);
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
    SetMovementSpeedTag(NewSpeedLevel.SpeedTag);

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

void AUhuSurvivalCharacter::AdjustMovementSpeed(int32 Delta)
{
    if (!MovementDataAsset) return;

    int32 CurrentIndex = MovementDataAsset->SpeedLevels.IndexOfByPredicate([this](const FMovementSpeedLevel& SpeedLevel) {
        return SpeedLevel.SpeedTag == CurrentSpeedTag;
    });

    if (CurrentIndex != INDEX_NONE)
    {
        int32 NewIndex = FMath::Clamp(CurrentIndex + Delta, 1, MovementDataAsset->SpeedLevels.Num() - 1);
        SetMovementSpeedTag(MovementDataAsset->SpeedLevels[NewIndex].SpeedTag);
    }
}

void AUhuSurvivalCharacter::RestorePreviousMovementSpeed()
{
    if (PreviousSpeedTag.IsValid())
    {
        SetMovementSpeedTag(PreviousSpeedTag);
    }
    else
    {
        // If no previous speed, set to default walking speed
        SetMovementSpeedTag(FUhuGameplayTags::Get().Movement_Speed_1);
    }
}

void AUhuSurvivalCharacter::RemoveAllMovementSpeedTags()
{
    if (AbilitySystemComponent)
    {
        for (const FMovementSpeedLevel& SpeedLevel : MovementDataAsset->SpeedLevels)
        {
            AbilitySystemComponent->RemoveLooseGameplayTag(SpeedLevel.SpeedTag);
        }
    }
}

void AUhuSurvivalCharacter::ApplyMovementSpeedTag(FGameplayTag SpeedTag)
{
    if (AbilitySystemComponent)
    {
        if (CurrentSpeedTag != FUhuGameplayTags::Get().Movement_Speed_0)
        {
            PreviousSpeedTag = CurrentSpeedTag;
        }
        CurrentSpeedTag = SpeedTag;
        AbilitySystemComponent->AddLooseGameplayTag(SpeedTag);
    }
}

