// UhuPlayerController.h
// Copyright by MykeUhu

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GameplayTagContainer.h"
#include "UhuPlayerController.generated.h"

class UInputAction;
class UUhuInputConfig;
class UUhuAbilitySystemComponent;

struct FInputActionValue;


UCLASS()
class SURVIVAL_API AUhuPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AUhuPlayerController();
	virtual void PlayerTick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

	//TODO: Movement 3rd Person
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> MoveAction;

	//TODO: Look with Mouse
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> LookAction;

	// Jump
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> JumpAction;

	//TODO: Scrolling Mousewheel to Set GameplayTags from Movement_Speed_0 to Movement_Speed_10
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> SpeedAdjustAction;

	//TODO: Clicking Mousewheel to Set GameplayTag to Movement_Speed_5
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> SpeedResetAction;

	// Open the EmoteWheel
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> EmoteWheelOpenAction;

	void Move(const FInputActionValue& InputActionValue);
	void Look(const FInputActionValue& InputActionValue);
	void Jump(const FInputActionValue& InputActionValue);
	void SpeedAdjust(const FInputActionValue& InputActionValue);
	void SpeedReset(const FInputActionValue& InputActionValue);
	void EmoteWheelOpen(const FInputActionValue& InputActionValue);

	void AbilityInputTagPressed(FGameplayTag InputTag);
	void AbilityInputTagReleased(FGameplayTag InputTag);
	void AbilityInputTagHeld(FGameplayTag InputTag);

	// For Blueprint DA_UhuInputconfig
	UPROPERTY(EditDefaultsOnly, Category="Input")
	TObjectPtr<UUhuInputConfig> InputConfig;

	UPROPERTY()
	TObjectPtr<UUhuAbilitySystemComponent> UhuAbilitySystemComponent;

	UUhuAbilitySystemComponent* GetASC();

	float ShortPressThreshold = 0.5f;

	
};
