// UhuSkillLevelingComponent.h
// Copyright by MykeUhu

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Components/ActorComponent.h"
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

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SURVIVAL_API UUhuSkillLevelingComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UUhuSkillLevelingComponent();

    virtual void BeginPlay() override;

    // Aktualisiere den Fortschritt einer Fähigkeit
    void UpdateSkillProgress(FGameplayTag SkillTag, float Progress);

    // Server-seitige Methode zur Aktualisierung der Bewegungsfähigkeiten
    UFUNCTION(Server, Reliable, WithValidation)
    void ServerUpdateMovementSkills(float WalkedDistanceKM, float RunDistanceKM);

    // Initialisiere die Attributpunkte
    void InitializeAttributePoints();

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Leveling")
    UDataTable* AttributeLevelingDataTable;

    UPROPERTY(BlueprintReadOnly, Category = "Leveling")
    int32 CurrentLevel;

    UPROPERTY(BlueprintReadOnly, Category = "Leveling")
    int32 AvailableSkillPoints;

    UPROPERTY(BlueprintReadOnly, Category = "Leveling")
    TArray<FSkillLevelData> SkillLevels;

    UFUNCTION()
    void OnMilestoneReached();

    void CheckForLevelUp(float TotalDistanceKM);
    void AwardSkillPoints(int32 Points);
    void LevelUpSkill(FGameplayTag SkillTag);

    UFUNCTION(Client, Reliable)
    void ClientUpdateSkillLevels(const TArray<FSkillLevelData>& NewSkillLevels);

    UFUNCTION(Client, Reliable)
    void ClientUpdateAvailableSkillPoints(int32 NewAvailableSkillPoints);

    UFUNCTION()
    void OnRep_SkillLevels();

    UFUNCTION()
    void OnRep_AvailableSkillPoints();
};
