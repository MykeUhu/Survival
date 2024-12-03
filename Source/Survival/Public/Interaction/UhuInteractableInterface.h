// UhuInteractableInterface.h
// Copyright by MykeUhu

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "UhuInteractableInterface.generated.h"

UINTERFACE(MinimalAPI)
class UUhuInteractableInterface : public UInterface
{
	GENERATED_BODY()
};

class SURVIVAL_API IUhuInteractableInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
	void Interact(AActor* Interactor);
};

