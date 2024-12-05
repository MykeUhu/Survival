// UhuSurvivalCharacter.cpp
// Copyright by MykeUhu

#include "Characters/UhuSurvivalCharacter.h"
#include "AbilitySystem/UhuAbilitySystemComponent.h"
#include "AbilitySystem/UhuAttributeSet.h"
#include "Components/UhuSkillLevelingComponent.h"
#include "Components/DistanceProgressionComponent.h"
#include "Data/UhuMovementDataAsset.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "UhuGameplayTags.h"
#include "Net/UnrealNetwork.h"

AUhuSurvivalCharacter::AUhuSurvivalCharacter()
{
    PrimaryActorTick.bCanEverTick = true;

    AbilitySystemComponent = CreateDefaultSubobject<UUhuAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
    AttributeSet = CreateDefaultSubobject<UUhuAttributeSet>(TEXT("AttributeSet"));
    SkillLevelingComponent = CreateDefaultSubobject<UUhuSkillLevelingComponent>(TEXT("SkillLevelingComponent"));
    DistanceProgressionComponent = CreateDefaultSubobject<UDistanceProgressionComponent>(TEXT("DistanceProgressionComponent"));
    
    TotalDistanceWalked = 0.0f;
    TotalDistanceRun = 0.0f;
    CurrentSpeedLevel = 4; // Default to walking speed
}

void AUhuSurvivalCharacter::PossessedBy(AController* NewController)
{
    Super::PossessedBy(NewController);

    AbilitySystemComponent->InitAbilityActorInfo(this, this);
    InitializeAttributes();
    GiveDefaultAbilities();
}

void AUhuSurvivalCharacter::OnRep_PlayerState()
{
    Super::OnRep_PlayerState();

    AbilitySystemComponent->InitAbilityActorInfo(this, this);
    InitializeAttributes();
}

void AUhuSurvivalCharacter::BeginPlay()
{
    Super::BeginPlay();
    
    if (MovementDataAsset && MovementDataAsset->DefaultSpeedTag.IsValid())
    {
        SetMovementSpeedTag(MovementDataAsset->DefaultSpeedTag);
    }
    
    if (MilestoneTable)
    {
        DistanceProgressionComponent->InitializeMilestones(MilestoneTable);
    }
    
    if (DistanceProgressionComponent)
    {
        DistanceProgressionComponent->OnMilestoneReached.AddDynamic(this, &AUhuSurvivalCharacter::OnMilestoneReached);
    }
}

void AUhuSurvivalCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    UpdateDistanceTraveled(DeltaTime);
}

void AUhuSurvivalCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
}

UAbilitySystemComponent* AUhuSurvivalCharacter::GetAbilitySystemComponent() const
{
    return AbilitySystemComponent;
}

float AUhuSurvivalCharacter::GetTotalDistanceWalkedKM() const
{
    return FMath::RoundToFloat((TotalDistanceWalked / 100000.0f) * 10.0f) / 10.0f;
}

float AUhuSurvivalCharacter::GetTotalDistanceRunKM() const
{
    return FMath::RoundToFloat((TotalDistanceRun / 100000.0f) * 10.0f) / 10.0f;
}

ECharacterClass AUhuSurvivalCharacter::GetCharacterClass_Implementation()
{
    return CharacterClass;
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

    const FMovementSpeedLevel SpeedLevel = MovementDataAsset->GetSpeedLevelForTag(NewSpeedTag);
    if (SpeedLevel.Speed >= 0.f)
    {
        ApplyMovementSpeed(SpeedLevel.Speed);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Invalid Speed Level for Tag: %s"), *NewSpeedTag.ToString());
    }
}

void AUhuSurvivalCharacter::ApplyMovementSpeed(float Speed)
{
    if (HasAuthority())
    {
        MaxWalkSpeed = Speed; // Setzen der Geschwindigkeit auf dem Server
        OnRep_MovementSpeed(); // Direkte Anwendung auf dem Server
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

void AUhuSurvivalCharacter::OnRep_MovementSpeed()
{
    // Anwenden der replizierten Geschwindigkeit auf die Bewegungskomponente
    if (GetCharacterMovement())
    {
        GetCharacterMovement()->MaxWalkSpeed = MaxWalkSpeed;
    }
}

void AUhuSurvivalCharacter::OnMilestoneReached()
{
    UE_LOG(LogTemp, Log, TEXT("Milestone reached! Triggering event with Gameplay Tag."));
    // Add any additional logic for milestone reached event
}

void AUhuSurvivalCharacter::InitializeAttributes()
{
    if (AbilitySystemComponent && DefaultVitalAttributes)
    {
        FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
        EffectContext.AddSourceObject(this);

        FGameplayEffectSpecHandle NewHandle = AbilitySystemComponent->MakeOutgoingSpec(DefaultVitalAttributes, 1, EffectContext);
        if (NewHandle.IsValid())
        {
            AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*NewHandle.Data.Get());
        }
    }
}

void AUhuSurvivalCharacter::GiveDefaultAbilities()
{
    if (AbilitySystemComponent)
    {
        for (TSubclassOf<UGameplayAbility>& StartupAbility : StartupAbilities)
        {
            AbilitySystemComponent->GiveAbility(
                FGameplayAbilitySpec(StartupAbility, 1, INDEX_NONE, this));
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

void AUhuSurvivalCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    // Füge MaxWalkSpeed zur Replikationsliste hinzu
    DOREPLIFETIME(AUhuSurvivalCharacter, MaxWalkSpeed);
}