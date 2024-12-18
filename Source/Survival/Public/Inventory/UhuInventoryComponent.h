// UhuInventoryComponent.h
// Copyright by MykeUhu

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "UhuInventoryComponent.generated.h"

USTRUCT(BlueprintType)
struct FInventoryItem
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString ItemName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Quantity = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Weight = 0.0f;
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SURVIVAL_API UUhuInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:    
	UUhuInventoryComponent();

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool AddItem(const FInventoryItem& Item);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool RemoveItem(const FString& ItemName, int32 Quantity);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	TArray<FInventoryItem> GetInventory() const;

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	float GetTotalWeight() const;

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool HasItem(const FString& ItemName, int32 Quantity = 1) const;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere, Category = "Inventory")
	TArray<FInventoryItem> Inventory;

	UPROPERTY(EditAnywhere, Category = "Inventory")
	float MaxWeight;
};

