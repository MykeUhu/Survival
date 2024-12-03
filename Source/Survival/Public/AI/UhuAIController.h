// UhuAIController.h
// Copyright by MykeUhu

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "UhuAIController.generated.h"

UCLASS()
class SURVIVAL_API AUhuAIController : public AAIController
{
	GENERATED_BODY()

public:
	AUhuAIController();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
	class UBehaviorTree* BehaviorTree;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
	float SightRadius = 500.0f;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
	float LoseSightRadius = 600.0f;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
	float PeripheralVisionAngleDegrees = 60.0f;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
	float HearingRange = 1000.0f;

private:
	UPROPERTY()
	class UAISenseConfig_Sight* SightConfig;

	UPROPERTY()
	class UAISenseConfig_Hearing* HearingConfig;

	void SetupPerceptionSystem();
};

