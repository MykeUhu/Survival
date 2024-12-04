// UhuSkillLevelingComponent.h
// Copyright by MykeUhu

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameplayTagContainer.h"
#include "Data/UhuAttributeLevelingDataTable.h"
#include "UhuSkillLevelingComponent.generated.h"

USTRUCT(BlueprintType)
struct FSkillLevelData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FGameplayTag SkillTag;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 Level = 1;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Experience = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float ExperienceRequiredForNextLevel = 100.0f;
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SURVIVAL_API UUhuSkillLevelingComponent : public UActorComponent
{
    GENERATED_BODY()

public:    
    UUhuSkillLevelingComponent();

    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

    UFUNCTION(BlueprintCallable, Category = "Skill Leveling")
    void UpdateSkillProgress(FGameplayTag SkillTag, float Progress);

    UFUNCTION(BlueprintCallable, Category = "Skill Leveling")
    FSkillLevelData GetSkillLevelData(FGameplayTag SkillTag) const;

    UFUNCTION(Server, Reliable, WithValidation)
    void ServerUpdateMovementSkills(float WalkedDistanceKM, float RunDistanceKM);

    UFUNCTION(BlueprintCallable, Category = "Skill Leveling")
    int32 GetAvailableSkillPoints() const { return AvailableSkillPoints; }

    UFUNCTION(Server, Reliable, WithValidation)
    void ServerApplySkillPointToAttribute(FGameplayTag AttributeTag);

protected:
    virtual void BeginPlay() override;

private:
    UPROPERTY(EditDefaultsOnly, Category = "Skill Leveling")
    UDataTable* AttributeLevelingDataTable;

    UPROPERTY(Replicated)
    int32 CurrentLevel;

    UPROPERTY(ReplicatedUsing = OnRep_AvailableSkillPoints)
    int32 AvailableSkillPoints;

    UPROPERTY(ReplicatedUsing = OnRep_SkillLevels)
    TArray<FSkillLevelData> SkillLevels;

    UFUNCTION()
    void OnRep_SkillLevels();

    UFUNCTION()
    void OnRep_AvailableSkillPoints();

    void LevelUpSkill(FGameplayTag SkillTag);
    void CheckForLevelUp(float TotalDistanceKM);
    void AwardSkillPoints(int32 Points);

    UFUNCTION(Client, Reliable)
    void ClientUpdateSkillLevels(const TArray<FSkillLevelData>& NewSkillLevels);

    UFUNCTION(Client, Reliable)
    void ClientUpdateAvailableSkillPoints(int32 NewAvailableSkillPoints);
};

