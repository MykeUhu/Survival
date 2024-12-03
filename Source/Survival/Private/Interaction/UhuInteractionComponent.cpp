// UhuInteractionComponent.cpp
// Copyright by MykeUhu

#include "Interaction/UhuInteractionComponent.h"
#include "Interaction/UhuInteractableInterface.h"

UUhuInteractionComponent::UUhuInteractionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UUhuInteractionComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UUhuInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FindInteractable();
}

void UUhuInteractionComponent::Interact()
{
	if (CurrentInteractable)
	{
		IUhuInteractableInterface::Execute_Interact(CurrentInteractable, GetOwner());
	}
}

void UUhuInteractionComponent::FindInteractable()
{
	AActor* OwningActor = GetOwner();
	if (!OwningActor) return;

	FVector Start = OwningActor->GetActorLocation();
	FVector End = Start + OwningActor->GetActorForwardVector() * InteractionRange;

	FHitResult HitResult;
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(OwningActor);

	if (GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility, QueryParams))
	{
		AActor* HitActor = HitResult.GetActor();
		if (HitActor && HitActor->Implements<UUhuInteractableInterface>())
		{
			if (CurrentInteractable != HitActor)
			{
				CurrentInteractable = HitActor;
				OnInteractableFound.Broadcast(CurrentInteractable);
			}
			return;
		}
	}

	if (CurrentInteractable)
	{
		CurrentInteractable = nullptr;
		OnInteractableFound.Broadcast(nullptr);
	}
}

