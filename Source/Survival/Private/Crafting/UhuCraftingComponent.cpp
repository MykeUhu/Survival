// UhuCraftingComponent.cpp
// Copyright by MykeUhu

#include "Crafting/UhuCraftingComponent.h"
#include "Inventory/UhuInventoryComponent.h"

UUhuCraftingComponent::UUhuCraftingComponent(): InventoryComponent(nullptr)
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UUhuCraftingComponent::SetupInventoryComponent()
{
	AActor* Owner = GetOwner();
	if (Owner)
	{
		InventoryComponent = Owner->FindComponentByClass<UUhuInventoryComponent>();
	}
}

bool UUhuCraftingComponent::CraftItem(const FCraftingRecipe& Recipe)
{
	if (!InventoryComponent)
	{
		SetupInventoryComponent();
		if (!InventoryComponent) return false;
	}

	// Check if we have all the ingredients
	for (const auto& Ingredient : Recipe.Ingredients)
	{
		if (!InventoryComponent->HasItem(Ingredient.Key, Ingredient.Value))
		{
			return false;
		}
	}

	// Remove ingredients from inventory
	for (const auto& Ingredient : Recipe.Ingredients)
	{
		InventoryComponent->RemoveItem(Ingredient.Key, Ingredient.Value);
	}

	// Add crafted item to inventory
	FInventoryItem CraftedItem;
	CraftedItem.ItemName = Recipe.ResultItemName;
	CraftedItem.Quantity = Recipe.ResultQuantity;
	// Note: You might want to set the weight of the crafted item here

	InventoryComponent->AddItem(CraftedItem);

	return true;
}

void UUhuCraftingComponent::AddRecipe(const FCraftingRecipe& Recipe)
{
	AvailableRecipes.Add(Recipe);
}

TArray<FCraftingRecipe> UUhuCraftingComponent::GetAvailableRecipes() const
{
	return AvailableRecipes;
}

