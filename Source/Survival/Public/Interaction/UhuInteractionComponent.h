// UhuInteractionComponent.h
// Copyright by MykeUhu

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "UhuInteractionComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInteractableFound, AActor*, InteractableActor);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SURVIVAL_API UUhuInteractionComponent : public UActorComponent
{
	GENERATED_BODY()

public:    
	UUhuInteractionComponent();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = "Interaction")
	void Interact();

	UPROPERTY(BlueprintAssignable, Category = "Interaction")
	FOnInteractableFound OnInteractableFound;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, Category = "Interaction")
	float InteractionRange = 200.f;

	UPROPERTY()
	AActor* CurrentInteractable;

	void FindInteractable();
};

