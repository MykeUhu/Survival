// UhuHUD.h
// Copyright by MykeUhu

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "UhuHUD.generated.h"

UCLASS()
class SURVIVAL_API AUhuHUD : public AHUD
{
	GENERATED_BODY()

public:
	AUhuHUD();

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent, Category = "UI")
	void CreateMainUI();

	UFUNCTION(BlueprintImplementableEvent, Category = "UI")
	void UpdateHealthUI(float CurrentHealth, float MaxHealth);

	UFUNCTION(BlueprintImplementableEvent, Category = "UI")
	void UpdateStaminaUI(float CurrentStamina, float MaxStamina);

	UFUNCTION(BlueprintImplementableEvent, Category = "UI")
	void UpdateInventoryUI();

protected:
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<class UUserWidget> MainUIClass;

	UPROPERTY()
	class UUserWidget* MainUIWidget;
};

