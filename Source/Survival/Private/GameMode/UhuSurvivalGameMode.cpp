// UhuSurvivalGameMode.cpp
// Copyright by MykeUhu

#include "GameMode/UhuSurvivalGameMode.h"
#include "Characters/UhuSurvivalCharacter.h"
#include "UI/UhuHUD.h"

AUhuSurvivalGameMode::AUhuSurvivalGameMode()
{
	DefaultPawnClass = AUhuSurvivalCharacter::StaticClass();
	// Set default classes
	HUDClass = AUhuHUD::StaticClass();
	MaxPlayers = 4;
	DayNightCycleDuration = 1200.0f; // 20 minutes
}

void AUhuSurvivalGameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);

	// Initialize any game-specific systems here
}

void AUhuSurvivalGameMode::HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer)
{
	Super::HandleStartingNewPlayer_Implementation(NewPlayer);

	// Perform any player-specific initialization here
}


