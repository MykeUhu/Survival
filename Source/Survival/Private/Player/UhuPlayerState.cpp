// UhuPlayerState.cpp
// Copyright by MykeUhu

#include "Player/UhuPlayerState.h"

#include "AbilitySystem/UhuAbilitySystemComponent.h"
#include "AbilitySystem/UhuAttributeSet.h"
#include "Net/UnrealNetwork.h"


AUhuPlayerState::AUhuPlayerState()
{
	AbilitySystemComponent = CreateDefaultSubobject<UUhuAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	AttributeSet = CreateDefaultSubobject<UUhuAttributeSet>("AttributeSet");
	
	SetNetUpdateFrequency(100.f);
}

void AUhuPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME(AUhuPlayerState, Level);
}

UAbilitySystemComponent* AUhuPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void AUhuPlayerState::SetLevel(int32 InLevel)
{
	Level = InLevel;
	OnLevelChangedDelegate.Broadcast(Level);
}

void AUhuPlayerState::OnRep_Level(int32 OldLevel)
{
	OnLevelChangedDelegate.Broadcast(Level);
}


