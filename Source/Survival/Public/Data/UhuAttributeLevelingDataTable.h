// UhuAttributeLevelingDataTable.h
// Copyright by MykeUhu

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "UhuAttributeLevelingDataTable.generated.h"

USTRUCT(BlueprintType)
struct FUhuAttributeLevelingTableRow : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Leveling")
	float WalkDistanceKM = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Leveling")
	float WalkXPMultiplier = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Leveling")
	float RunDistanceKM = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Leveling")
	float RunXPMultiplier = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Leveling")
	float CraftingXPRequired = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Leveling")
	float SurvivalXPRequired = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Leveling")
	int32 SkillPointsAwarded = 0;
};