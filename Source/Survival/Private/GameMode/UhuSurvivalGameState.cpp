// UhuSurvivalGameState.cpp
// Copyright by MykeUhu

#include "GameMode/UhuSurvivalGameState.h"
#include "Net/UnrealNetwork.h"

AUhuSurvivalGameState::AUhuSurvivalGameState()
{
	PrimaryActorTick.bCanEverTick = true;
	TimeOfDay = 0.0f;
}

void AUhuSurvivalGameState::SetTimeOfDay(float NewTime)
{
	TimeOfDay = FMath::Fmod(NewTime, 24.0f);
}

void AUhuSurvivalGameState::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	TimeOfDay += DeltaSeconds * TimeScale / 3600.0f; // Convert seconds to hours
	if (TimeOfDay >= 24.0f)
	{
		TimeOfDay -= 24.0f;
	}
}

void AUhuSurvivalGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AUhuSurvivalGameState, TimeOfDay);
}

