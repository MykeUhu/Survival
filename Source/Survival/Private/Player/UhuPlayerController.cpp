// UhuPlayerController.cpp
// Copyright by MykeUhu

#include "Player/UhuPlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystem/UhuAbilitySystemComponent.h"
#include "Data/UhuMovementDataAsset.h"
#include "Characters/UhuSurvivalCharacter.h"

AUhuPlayerController::AUhuPlayerController()
{
    bReplicates = true;
}

void AUhuPlayerController::BeginPlay()
{
    Super::BeginPlay();
    
    if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
    {
        Subsystem->AddMappingContext(DefaultMappingContext, 0);
    }
}

void AUhuPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();

    if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent))
    {
        EnhancedInputComponent->BindAction(SpeedAdjustAction, ETriggerEvent::Triggered, this, &AUhuPlayerController::AdjustSpeedWithMouseWheel);
    }
}

void AUhuPlayerController::AdjustSpeedWithMouseWheel(const FInputActionValue& InputValue)
{
    const float Delta = InputValue.GetMagnitude();
    const int32 NewSpeedIndex = FMath::Clamp(CurrentSpeedIndex + (Delta > 0 ? 1 : -1), 0, MovementDataAsset->SpeedLevels.Num() - 1);

    if (NewSpeedIndex != CurrentSpeedIndex)
    {
        UpdateMovementSpeedTag(NewSpeedIndex);
        CurrentSpeedIndex = NewSpeedIndex;
    }
}

void AUhuPlayerController::UpdateMovementSpeedTag(int32 SpeedIndex)
{
    if (!MovementDataAsset || !MovementDataAsset->SpeedLevels.IsValidIndex(SpeedIndex))
    {
        return;
    }

    const FGameplayTag NewSpeedTag = MovementDataAsset->SpeedLevels[SpeedIndex].SpeedTag;
    const FGameplayTag OldSpeedTag = MovementDataAsset->SpeedLevels[CurrentSpeedIndex].SpeedTag;

    if (AUhuSurvivalCharacter* ControlledCharacter = Cast<AUhuSurvivalCharacter>(GetPawn()))
    {
        ControlledCharacter->UpdateMovementSpeed(SpeedIndex);
    }
}

UUhuAbilitySystemComponent* AUhuPlayerController::GetASC()
{
    if (UhuAbilitySystemComponent == nullptr)
    {
        UhuAbilitySystemComponent = Cast<UUhuAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetPawn<APawn>()));
    }
    return UhuAbilitySystemComponent;
}