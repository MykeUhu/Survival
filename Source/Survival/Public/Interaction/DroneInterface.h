// DroneInterface.h
// Copyright by MykeUhu

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "DroneInterface.generated.h"

UINTERFACE(MinimalAPI)
class UDroneInterface : public UInterface
{
	GENERATED_BODY()
};

class SURVIVAL_API IDroneInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Companion")
	void ExecuteCommand(const FString& Command);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Companion")
	void FollowPlayer(AActor* Player);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Companion")
	void StopFollowing();
};