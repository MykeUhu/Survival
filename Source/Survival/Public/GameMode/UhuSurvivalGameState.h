// UhuSurvivalGameState.h
// Copyright by MykeUhu

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "UhuSurvivalGameState.generated.h"

UCLASS()
class SURVIVAL_API AUhuSurvivalGameState : public AGameStateBase
{
	GENERATED_BODY()

public:
	AUhuSurvivalGameState();

	UFUNCTION(BlueprintCallable, Category = "Game State")
	float GetTimeOfDay() const { return TimeOfDay; }

	UFUNCTION(BlueprintCallable, Category = "Game State")
	void SetTimeOfDay(float NewTime);

	virtual void Tick(float DeltaSeconds) override;

protected:
	UPROPERTY(Replicated, BlueprintReadOnly, Category = "Game State")
	float TimeOfDay;

	UPROPERTY(EditDefaultsOnly, Category = "Game State")
	float TimeScale = 1.0f;
};

