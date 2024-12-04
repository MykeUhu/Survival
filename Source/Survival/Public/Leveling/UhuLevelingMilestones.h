// UhuLevelingMilestones.h
// Copyright by MykeUhu

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "GameplayTagContainer.h"
#include "UhuLevelingMilestones.generated.h"

// Belohnungsstruktur
USTRUCT(BlueprintType)
struct FRewardData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 SkillPointsAwarded;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ExperiencePoints;

	// Weitere Belohnungen können hier ergänzt werden
};

// Datenstruktur für jeden Meilenstein
USTRUCT(BlueprintType)
struct FDistanceMilestone : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName MilestoneID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float RequiredDistanceKM;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FRewardData Reward;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayTag TriggerEvent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSoftObjectPtr<UParticleSystem> VisualEffect;
};
