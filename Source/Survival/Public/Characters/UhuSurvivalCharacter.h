// UhuSurvivalCharacter.h
// Copyright by MykeUhu

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffect.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "UhuSurvivalCharacter.generated.h"

class UUhuMovementDataAsset;

UCLASS(config=Game)
class SURVIVAL_API AUhuSurvivalCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AUhuSurvivalCharacter();
    
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable, Category = "Uhu|Movement")
	void UpdateMovementSpeed(int32 SpeedLevel);

	// Implement IAbilitySystemInterface
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	//TODO: UPROPERTY and implementation for StartupAbilities (DataTable or DataAsset, in BP derived from a C++
	//TODO: UPROPERTY for AttribueInfo and implementation

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "GAS|Attributes")
	TSubclassOf<UGameplayEffect> DefaultVitalAttributes;
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "GAS|Attributes")
	TSubclassOf<UGameplayEffect> DefaultPrimaryAttributes;
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "GAS|Attributes")
	TSubclassOf<UGameplayEffect> DefaultSecondaryAttributes;

	// TODO: chekc if this is correct, lots of derived functions in code
	UPROPERTY(EditDefaultsOnly, Category = "GAS|Movement")
	UUhuMovementDataAsset* MovementDataAsset;
	
	void ApplyEffectToSelf(TSubclassOf<UGameplayEffect> GameplayEffectClass, float Level) const;
	virtual void InitializeDefaultAttributes() const;

private:
	//TODO: Implement Startup Abilities
	UPROPERTY(EditAnywhere, Category = "GAS|Abilities")
	TArray<TSubclassOf<UGameplayAbility>> StartupAbilities;

	// TODO: Check if we need or add in ApplyEffectToSelf
	UPROPERTY(EditDefaultsOnly, Category = "GAS|Movement")
	TSubclassOf<UGameplayEffect> MovementSpeedEffect;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Abilities", meta = (AllowPrivateAccess = "true"))
	UAbilitySystemComponent* AbilitySystemComponent;

	int32 CurrentSpeedLevel = 4;
};
