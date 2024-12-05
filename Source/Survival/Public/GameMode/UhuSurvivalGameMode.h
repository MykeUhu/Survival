// UhuSurvivalGameMode.h
// Copyright by MykeUhu

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Data/AbilityInfo.h"
#include "AbilitySystem/Data/CharacterClassInfo.h"
#include "GameFramework/GameModeBase.h"
#include "UhuSurvivalGameMode.generated.h"

UCLASS(minimalapi)
class AUhuSurvivalGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AUhuSurvivalGameMode();

	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;
	virtual void HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer) override;

	UPROPERTY(EditDefaultsOnly, Category = "Character Class Defaults")
	TObjectPtr<UCharacterClassInfo> CharacterClassInfo;

	UPROPERTY(EditDefaultsOnly, Category = "Ability Info")
	TObjectPtr<UAbilityInfo> AbilityInfo;

protected:
	
	UPROPERTY(EditDefaultsOnly, Category = "Game Rules")
	int32 MaxPlayers;

	UPROPERTY(EditDefaultsOnly, Category = "Game Rules")
	float DayNightCycleDuration;


};

