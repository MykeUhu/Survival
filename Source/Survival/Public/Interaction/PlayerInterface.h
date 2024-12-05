// PlayerInterface.h
// Copyright by MykeUhu

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PlayerInterface.generated.h"

UINTERFACE(MinimalAPI)
class UPlayerInterface : public UInterface
{
	GENERATED_BODY()
};

class SURVIVAL_API IPlayerInterface
{
	GENERATED_BODY()

public:
	// Attribute-Management
	UFUNCTION(BlueprintNativeEvent)
	int32 GetAttributePoints() const;

	UFUNCTION(BlueprintNativeEvent)
	void AddToAttributePoints(int32 InAttributePoints);

	// Interaktion
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
	void Interact(AActor* Interactor);

	// Drohnen-Interaktion
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Companion")
	void CommandCompanion(const FString& Command);
};