// DistanceProgressionComponent.h
// Copyright by MykeUhu

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Leveling/UhuLevelingMilestones.h"
#include "DistanceProgressionComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SURVIVAL_API UDistanceProgressionComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UDistanceProgressionComponent();

	virtual void BeginPlay() override;

	// Distanzupdate vom Character
	void UpdateDistance(float DistanceDelta);

	// Initialisiere mit DataTable
	void InitializeMilestones(UDataTable* MilestoneTable);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Progression")
	UDataTable* MilestoneTable;

	UPROPERTY(BlueprintReadOnly, Category = "Progression")
	float TotalDistance;

	UPROPERTY(BlueprintReadOnly, Category = "Progression")
	int32 CurrentMilestoneIndex;

	UFUNCTION()
	void CheckForNextMilestone();
};
