// UhuSkillLevelingComponent.h
// Copyright by MykeUhu

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameplayTagContainer.h"
#include "UhuSkillLevelingComponent.generated.h"

USTRUCT(BlueprintType)
struct FSkillLevelData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Level;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Experience;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ExperienceRequiredForNextLevel;
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SURVIVAL_API UUhuSkillLevelingComponent : public UActorComponent
{
	GENERATED_BODY()

public:    
	UUhuSkillLevelingComponent();

	UFUNCTION(BlueprintCallable, Category = "Skill Leveling")
	void UpdateSkillProgress(FGameplayTag SkillTag, float Progress);

	UFUNCTION(BlueprintCallable, Category = "Skill Leveling")
	FSkillLevelData GetSkillLevelData(FGameplayTag SkillTag) const;

	UFUNCTION(BlueprintCallable, Category = "Skill Leveling")
	void UpdateRunningSkill(float Distance);

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY()
	TMap<FGameplayTag, FSkillLevelData> SkillLevels;

	UPROPERTY(EditDefaultsOnly, Category = "Skill Leveling")
	TMap<FGameplayTag, UCurveFloat*> ExperienceCurves;

	void LevelUpSkill(FGameplayTag SkillTag);
};

