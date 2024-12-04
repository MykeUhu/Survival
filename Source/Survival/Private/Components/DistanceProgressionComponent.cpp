// DistanceProgressionComponent.cpp
// Copyright by MykeUhu

#include "Components/DistanceProgressionComponent.h"
#include "Net/UnrealNetwork.h"

UDistanceProgressionComponent::UDistanceProgressionComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	TotalDistance = 0.0f;
	CurrentMilestoneIndex = -1;
	SetIsReplicatedByDefault(true);

	// Initialisiere die DataTable als nullptr
	MilestoneTable = nullptr;
}

void UDistanceProgressionComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UDistanceProgressionComponent::InitializeMilestones(UDataTable* InMilestoneTable)
{
	MilestoneTable = InMilestoneTable;
}

void UDistanceProgressionComponent::UpdateDistance(float DistanceDelta)
{
	TotalDistance += DistanceDelta;

	// Prüfe, ob ein neuer Meilenstein erreicht wurde
	CheckForNextMilestone();
}

void UDistanceProgressionComponent::CheckForNextMilestone()
{
	if (!MilestoneTable) return;

	FString Context;
	TArray<FName> RowNames = MilestoneTable->GetRowNames();

	for (int32 i = CurrentMilestoneIndex + 1; i < RowNames.Num(); i++)
	{
		FDistanceMilestone* Milestone = MilestoneTable->FindRow<FDistanceMilestone>(RowNames[i], Context);
		if (Milestone && TotalDistance >= Milestone->RequiredDistanceKM)
		{
			CurrentMilestoneIndex = i;

			// Hier können Belohnungen, Events usw. ausgelöst werden
			UE_LOG(LogTemp, Log, TEXT("Meilenstein erreicht: %s"), *Milestone->MilestoneID.ToString());
		}
	}
}
