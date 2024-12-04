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
	float WalkDistanceKM;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Leveling")
	float WalkXPMultiplier;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Leveling")
	float RunDistanceKM;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Leveling")
	float RunXPMultiplier;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Leveling")
	float CraftingXPRequired;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Leveling")
	float SurvivalXPRequired;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Leveling")
	int32 SkillPointsAwarded;
};

