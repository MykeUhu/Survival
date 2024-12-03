// UhuInventoryComponent.cpp
// Copyright by MykeUhu

#include "Inventory/UhuInventoryComponent.h"

UUhuInventoryComponent::UUhuInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	MaxWeight = 100.0f; // Default max weight
}

void UUhuInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
}

bool UUhuInventoryComponent::AddItem(const FInventoryItem& Item)
{
	if (GetTotalWeight() + Item.Weight * Item.Quantity > MaxWeight)
	{
		return false; // Exceeds max weight
	}

	for (FInventoryItem& ExistingItem : Inventory)
	{
		if (ExistingItem.ItemName == Item.ItemName)
		{
			ExistingItem.Quantity += Item.Quantity;
			return true;
		}
	}

	Inventory.Add(Item);
	return true;
}

bool UUhuInventoryComponent::RemoveItem(const FString& ItemName, int32 Quantity)
{
	for (int32 i = 0; i < Inventory.Num(); i++)
	{
		if (Inventory[i].ItemName == ItemName)
		{
			if (Inventory[i].Quantity >= Quantity)
			{
				Inventory[i].Quantity -= Quantity;
				if (Inventory[i].Quantity == 0)
				{
					Inventory.RemoveAt(i);
				}
				return true;
			}
		}
	}
	return false;
}

TArray<FInventoryItem> UUhuInventoryComponent::GetInventory() const
{
	return Inventory;
}

float UUhuInventoryComponent::GetTotalWeight() const
{
	float TotalWeight = 0.0f;
	for (const FInventoryItem& Item : Inventory)
	{
		TotalWeight += Item.Weight * Item.Quantity;
	}
	return TotalWeight;
}

bool UUhuInventoryComponent::HasItem(const FString& Key, int Value)
{
	for (const FInventoryItem& Item : Inventory)
	{
		if (Item.ItemName == Key && Item.Quantity >= Value)
		{
			return true;
		}
	}
	return false;
}
