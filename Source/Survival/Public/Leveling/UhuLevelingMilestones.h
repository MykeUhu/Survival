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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rewards")
	int32 SkillPointsAwarded = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rewards")
	float ExperiencePoints = 0.0f;
};

// Datenstruktur für jeden Meilenstein
USTRUCT(BlueprintType)
struct FDistanceMilestone : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName MilestoneID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Milestone")
	float RequiredDistanceKM = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Milestone")
	FRewardData Reward;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayTag TriggerEvent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSoftObjectPtr<UParticleSystem> VisualEffect;
};
