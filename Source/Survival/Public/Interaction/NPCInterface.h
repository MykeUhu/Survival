// NPCInterface.h
// Copyright by MykeUhu

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "NPCInterface.generated.h"

UINTERFACE(MinimalAPI)
class UNPCInterface : public UInterface
{
	GENERATED_BODY()
};

class SURVIVAL_API INPCInterface
{
	GENERATED_BODY()

public:
	// NPC-Interaktionen
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
	void OnInteract(AActor* Interactor);
};