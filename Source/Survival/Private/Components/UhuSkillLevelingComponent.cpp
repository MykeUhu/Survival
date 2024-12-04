// UhuSkillLevelingComponent.cpp
// Copyright by MykeUhu

#include "Components/UhuSkillLevelingComponent.h"
#include "UhuGameplayTags.h"
#include "AbilitySystemComponent.h"
#include "GameplayEffectTypes.h"
#include "Net/UnrealNetwork.h"

UUhuSkillLevelingComponent::UUhuSkillLevelingComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
    CurrentLevel = 1;
    AvailableSkillPoints = 0;
    SetIsReplicatedByDefault(true);
}

void UUhuSkillLevelingComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(UUhuSkillLevelingComponent, SkillLevels);
    DOREPLIFETIME(UUhuSkillLevelingComponent, CurrentLevel);
    DOREPLIFETIME(UUhuSkillLevelingComponent, AvailableSkillPoints);
}

void UUhuSkillLevelingComponent::BeginPlay()
{
    Super::BeginPlay();

    // Initialize skill levels
    const FUhuGameplayTags& GameplayTags = FUhuGameplayTags::Get();
    SkillLevels.Add(FSkillLevelData{GameplayTags.Skill_Running, 1, 0.0f, 100.0f});
    SkillLevels.Add(FSkillLevelData{GameplayTags.Skill_Walking, 1, 0.0f, 100.0f});
    SkillLevels.Add(FSkillLevelData{GameplayTags.Skill_Crafting, 1, 0.0f, 100.0f});
    SkillLevels.Add(FSkillLevelData{GameplayTags.Skill_Survival, 1, 0.0f, 100.0f});
}

void UUhuSkillLevelingComponent::UpdateSkillProgress(FGameplayTag SkillTag, float Progress)
{
    if (GetOwnerRole() != ROLE_Authority) return;

    FSkillLevelData* SkillData = SkillLevels.FindByPredicate([SkillTag](const FSkillLevelData& Data) { return Data.SkillTag == SkillTag; });
    if (SkillData)
    {
        SkillData->Experience += Progress;
        
        if (SkillData->Experience >= SkillData->ExperienceRequiredForNextLevel)
        {
            LevelUpSkill(SkillTag);
        }

        ClientUpdateSkillLevels(SkillLevels);
    }
}

FSkillLevelData UUhuSkillLevelingComponent::GetSkillLevelData(FGameplayTag SkillTag) const
{
    const FSkillLevelData* SkillData = SkillLevels.FindByPredicate([SkillTag](const FSkillLevelData& Data) { return Data.SkillTag == SkillTag; });
    return SkillData ? *SkillData : FSkillLevelData();
}

void UUhuSkillLevelingComponent::ServerUpdateMovementSkills_Implementation(float WalkedDistanceKM, float RunDistanceKM)
{
    if (!AttributeLevelingDataTable)
    {
        UE_LOG(LogTemp, Error, TEXT("Attribute Leveling Data Table is not set in UhuSkillLevelingComponent"));
        return;
    }

    const FUhuGameplayTags& GameplayTags = FUhuGameplayTags::Get();
    float TotalDistanceKM = WalkedDistanceKM + RunDistanceKM;

    FString ContextString;
    FUhuAttributeLevelingTableRow* Row = AttributeLevelingDataTable->FindRow<FUhuAttributeLevelingTableRow>(FName(*FString::FromInt(CurrentLevel)), ContextString);
    
    if (Row)
    {
        float WalkXP = WalkedDistanceKM * Row->WalkXPMultiplier;
        float RunXP = RunDistanceKM * Row->RunXPMultiplier;

        UpdateSkillProgress(GameplayTags.Skill_Walking, WalkXP);
        UpdateSkillProgress(GameplayTags.Skill_Running, RunXP);

        CheckForLevelUp(TotalDistanceKM);
    }
}

bool UUhuSkillLevelingComponent::ServerUpdateMovementSkills_Validate(float WalkedDistanceKM, float RunDistanceKM)
{
    // Add validation logic here if needed
    return true;
}

void UUhuSkillLevelingComponent::LevelUpSkill(FGameplayTag SkillTag)
{
    FSkillLevelData* SkillData = SkillLevels.FindByPredicate([SkillTag](const FSkillLevelData& Data) { return Data.SkillTag == SkillTag; });
    if (SkillData)
    {
        SkillData->Level++;
        SkillData->Experience -= SkillData->ExperienceRequiredForNextLevel;

        // Update required experience for next level
        FString ContextString;
        FUhuAttributeLevelingTableRow* Row = AttributeLevelingDataTable->FindRow<FUhuAttributeLevelingTableRow>(FName(*FString::FromInt(SkillData->Level)), ContextString);
        if (Row)
        {
            SkillData->ExperienceRequiredForNextLevel = Row->WalkDistanceKM + Row->RunDistanceKM;
        }
        else
        {
            // Fallback to a simple linear progression if no row is found
            SkillData->ExperienceRequiredForNextLevel *= 1.5f;
        }

        // Notify clients about the level up
        ClientUpdateSkillLevels(SkillLevels);
    }
}

void UUhuSkillLevelingComponent::CheckForLevelUp(float TotalDistanceKM)
{
    FString ContextString;
    FUhuAttributeLevelingTableRow* NextLevelRow = AttributeLevelingDataTable->FindRow<FUhuAttributeLevelingTableRow>(FName(*FString::FromInt(CurrentLevel + 1)), ContextString);
    
    if (NextLevelRow && TotalDistanceKM >= (NextLevelRow->WalkDistanceKM + NextLevelRow->RunDistanceKM))
    {
        CurrentLevel++;
        AwardSkillPoints(NextLevelRow->SkillPointsAwarded);
        
        // Recursively check for multiple level ups
        CheckForLevelUp(TotalDistanceKM);
    }
}

void UUhuSkillLevelingComponent::AwardSkillPoints(int32 Points)
{
    AvailableSkillPoints += Points;
    ClientUpdateAvailableSkillPoints(AvailableSkillPoints);
}

void UUhuSkillLevelingComponent::ServerApplySkillPointToAttribute_Implementation(FGameplayTag AttributeTag)
{
    if (AvailableSkillPoints > 0)
    {
        AvailableSkillPoints--;
        
        // Apply the skill point to the specified attribute
        AActor* Owner = GetOwner();
        if (Owner)
        {
            UAbilitySystemComponent* ASC = Owner->FindComponentByClass<UAbilitySystemComponent>();
            if (ASC)
            {
                FGameplayEffectSpecHandle SpecHandle = ASC->MakeOutgoingSpec(nullptr, 1, ASC->MakeEffectContext());
                SpecHandle.Data->SetSetByCallerMagnitude(AttributeTag, 1.0f);
                ASC->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
                
                ClientUpdateAvailableSkillPoints(AvailableSkillPoints);
            }
        }
    }
}

bool UUhuSkillLevelingComponent::ServerApplySkillPointToAttribute_Validate(FGameplayTag AttributeTag)
{
    // Add validation logic here if needed
    return true;
}

void UUhuSkillLevelingComponent::OnRep_SkillLevels()
{
    // Notify UI or other systems about updated skill levels
}

void UUhuSkillLevelingComponent::OnRep_AvailableSkillPoints()
{
    // Notify UI about updated available skill points
}

void UUhuSkillLevelingComponent::ClientUpdateSkillLevels_Implementation(const TArray<FSkillLevelData>& NewSkillLevels)
{
    SkillLevels = NewSkillLevels;
    OnRep_SkillLevels();
}

void UUhuSkillLevelingComponent::ClientUpdateAvailableSkillPoints_Implementation(int32 NewAvailableSkillPoints)
{
    AvailableSkillPoints = NewAvailableSkillPoints;
    OnRep_AvailableSkillPoints();
}

