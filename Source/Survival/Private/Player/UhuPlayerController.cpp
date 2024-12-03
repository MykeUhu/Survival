// UhuPlayerController.cpp
// Copyright by MykeUhu

#include "Player/UhuPlayerController.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "GameplayTagContainer.h"
#include "UhuGameplayTags.h"
#include "AbilitySystem/UhuAbilitySystemComponent.h"

AUhuPlayerController::AUhuPlayerController()
{
	bReplicates = true;
}

void AUhuPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
}

void AUhuPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	bShowMouseCursor = false;

	// TODO: Change Begin Play to 3rd Person Game Settings
	FInputModeGameAndUI InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeData.SetHideCursorDuringCapture(false);
	SetInputMode(InputModeData);
	
}

void AUhuPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
}

void AUhuPlayerController::Move(const FInputActionValue& InputActionValue)
{
	// Implement Move Forward / Move Right
}

UUhuAbilitySystemComponent* AUhuPlayerController::GetASC()
{
	if (UhuAbilitySystemComponent == nullptr)
	{
		UhuAbilitySystemComponent = Cast<UUhuAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetPawn<APawn>()));
	}
	return UhuAbilitySystemComponent;
}

void AUhuPlayerController::Look(const FInputActionValue& InputActionValue)
{
	// Implement Look with Mouse
}

void AUhuPlayerController::Jump(const FInputActionValue& InputActionValue)
{
	// Implement Jump use GameplayTag during Jump, maybe StartJump StopJump Functions
}

void AUhuPlayerController::SpeedAdjust(const FInputActionValue& InputActionValue)
{
	// Mousewheel up -> Get actual GameplayTag add 1 to GameplayTag: Movement_Speed_X
	// Mousewheel down -> Get actual GameplayTag to subtract 1 to GameplayTag: Movement_Speed_X
	// Player should have only actual Tag for movement, Initialize StartupSpeed5 
}

void AUhuPlayerController::SpeedReset(const FInputActionValue& InputActionValue)
{
	// Clicking Middle MouseButton -> Set GameplayTag Movement_Speed_5
	
}

void AUhuPlayerController::EmoteWheelOpen(const FInputActionValue& InputActionValue)
{
	// Our Main UserInterface and Interaction Interface for Drone and other Stuff we want do
}

void AUhuPlayerController::AbilityInputTagPressed(FGameplayTag InputTag)
{
	// I am shure we need it later
	if (GetASC()) GetASC()->AbilityInputTagPressed(InputTag);
}

void AUhuPlayerController::AbilityInputTagReleased(FGameplayTag InputTag)
{
	// I am shure we need it later
	if (GetASC()) GetASC()->AbilityInputTagReleased(InputTag);
}

void AUhuPlayerController::AbilityInputTagHeld(FGameplayTag InputTag)
{
	// I am shure we need it later
	if (GetASC()) GetASC()->AbilityInputTagHeld(InputTag);
}
