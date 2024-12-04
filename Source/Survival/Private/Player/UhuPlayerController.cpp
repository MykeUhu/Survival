// UhuPlayerController.cpp
// Copyright by MykeUhu

#include "Player/UhuPlayerController.h"

#include "EnhancedInputComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "EnhancedInputSubsystems.h"
#include "UhuGameplayTags.h"
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
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AUhuPlayerController::Move);
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
		// Setze das Speed-Tag direkt im Character, der die Authority hat
		ControlledCharacter->SetMovementSpeedTag(NewSpeedTag);
	}
}

void AUhuPlayerController::Move(const FInputActionValue& InputValue)
{
	FVector2D MoveDirection = InputValue.Get<FVector2D>();

	if (AUhuSurvivalCharacter* ControlledCharacter = Cast<AUhuSurvivalCharacter>(GetPawn()))
	{
		// If the character is idle, restore the previous movement speed
		if (ControlledCharacter->GetCurrentSpeedTag().MatchesTag(FUhuGameplayTags::Get().Movement_Speed_0))
		{
			ControlledCharacter->RestorePreviousMovementSpeed();
		}

		ControlledCharacter->CharacterMove(MoveDirection);
	}
}

void AUhuPlayerController::AdjustSpeedWithMouseWheel(const FInputActionValue& InputValue)
{
	const float Delta = InputValue.GetMagnitude();
	if (AUhuSurvivalCharacter* ControlledCharacter = Cast<AUhuSurvivalCharacter>(GetPawn()))
	{
		ControlledCharacter->AdjustMovementSpeed(Delta > 0 ? 1 : -1);
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
