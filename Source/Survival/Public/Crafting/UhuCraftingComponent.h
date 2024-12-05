// UhuCraftingComponent.h
// Copyright by MykeUhu

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "UhuCraftingComponent.generated.h"

USTRUCT(BlueprintType)
struct FCraftingRecipe
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<FString, int32> Ingredients;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString ResultItemName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 ResultQuantity = 1;
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SURVIVAL_API UUhuCraftingComponent : public UActorComponent
{
	GENERATED_BODY()

public:    
	UUhuCraftingComponent();

	UFUNCTION(BlueprintCallable, Category = "Crafting")
	bool CraftItem(const FCraftingRecipe& Recipe);

	UFUNCTION(BlueprintCallable, Category = "Crafting")
	void AddRecipe(const FCraftingRecipe& Recipe);

	UFUNCTION(BlueprintCallable, Category = "Crafting")
	TArray<FCraftingRecipe> GetAvailableRecipes() const;

private:
	UPROPERTY()
	TArray<FCraftingRecipe> AvailableRecipes;

	UPROPERTY()
	class UUhuInventoryComponent* InventoryComponent;

	void SetupInventoryComponent();
};

