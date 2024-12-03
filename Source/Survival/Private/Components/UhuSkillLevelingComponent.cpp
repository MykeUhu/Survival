// UhuSkillLevelingComponent.cpp
// Copyright by MykeUhu

#include "Components/UhuSkillLevelingComponent.h"
#include "UhuGameplayTags.h"

UUhuSkillLevelingComponent::UUhuSkillLevelingComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void UUhuSkillLevelingComponent::BeginPlay()
{
    Super::BeginPlay();

    // Initialize skill levels
    const FUhuGameplayTags& GameplayTags = FUhuGameplayTags::Get();
    SkillLevels.Add(GameplayTags.Skill_Running, FSkillLevelData{1, 0.0f, 100.0f});
    SkillLevels.Add(GameplayTags.Skill_Walking, FSkillLevelData{1, 0.0f, 100.0f});
    SkillLevels.Add(GameplayTags.Skill_Crafting, FSkillLevelData{1, 0.0f, 100.0f});
    SkillLevels.Add(GameplayTags.Skill_Survival, FSkillLevelData{1, 0.0f, 100.0f});
}

void UUhuSkillLevelingComponent::UpdateSkillProgress(FGameplayTag SkillTag, float Progress)
{
    if (FSkillLevelData* SkillData = SkillLevels.Find(SkillTag))
    {
        SkillData->Experience += Progress;
        
        if (SkillData->Experience >= SkillData->ExperienceRequiredForNextLevel)
        {
            LevelUpSkill(SkillTag);
        }
    }
}

void UUhuSkillLevelingComponent::UpdateRunningSkill(float Distance)
{
    const FUhuGameplayTags& GameplayTags = FUhuGameplayTags::Get();
    UpdateSkillProgress(GameplayTags.Skill_Running, Distance);
}

FSkillLevelData UUhuSkillLevelingComponent::GetSkillLevelData(FGameplayTag SkillTag) const
{
    if (const FSkillLevelData* SkillData = SkillLevels.Find(SkillTag))
    {
        return *SkillData;
    }
    return FSkillLevelData();
}

void UUhuSkillLevelingComponent::LevelUpSkill(FGameplayTag SkillTag)
{
    if (FSkillLevelData* SkillData = SkillLevels.Find(SkillTag))
    {
        SkillData->Level++;
        SkillData->Experience -= SkillData->ExperienceRequiredForNextLevel;

        // Update required experience for next level using the curve
        if (UCurveFloat* ExperienceCurve = ExperienceCurves.FindRef(SkillTag))
        {
            SkillData->ExperienceRequiredForNextLevel = ExperienceCurve->GetFloatValue(SkillData->Level);
        }
        else
        {
            // Fallback to a simple linear progression if no curve is set
            SkillData->ExperienceRequiredForNextLevel *= 1.5f;
        }

        // TODO: Apply any effects or notify other systems about the level up
    }
}

