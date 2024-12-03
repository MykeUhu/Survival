// UhuPlayerController.h
// Copyright by MykeUhu

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GameplayTagContainer.h"
#include "InputActionValue.h"
#include "UhuPlayerController.generated.h"

class UUhuMovementDataAsset;
class UInputAction;
class UInputMappingContext;
class UUhuAbilitySystemComponent;

UCLASS()
class SURVIVAL_API AUhuPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AUhuPlayerController();

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> SpeedAdjustAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputMappingContext> DefaultMappingContext;

	UPROPERTY(EditAnywhere, Category = "Movement")
	TObjectPtr<UUhuMovementDataAsset> MovementDataAsset;
	
	void AdjustSpeedWithMouseWheel(const FInputActionValue& InputValue);
	void UpdateMovementSpeedTag(int32 SpeedIndex);

	void Move(const FInputActionValue& InputValue);
	
	UFUNCTION(BlueprintCallable, Category = "AbilitySystem")
	UUhuAbilitySystemComponent* GetASC();

private:
	int32 CurrentSpeedIndex = 4; // Default index (middle speed)
    
	UPROPERTY()
	TObjectPtr<UUhuAbilitySystemComponent> UhuAbilitySystemComponent;
};