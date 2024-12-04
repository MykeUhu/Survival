// UhuAbilitySystemLibrary.cpp
// Copyright by MykeUhu

#include "AbilitySystem/UhuAbilitySystemLibrary.h"

#include "AbilitySystem/UhuAbilitySystemLibrary.h"
#include "UhuGameplayTags.h"
#include "GameMode/UhuSurvivalGameMode.h"
#include "AbilitySystem/Data/CharacterClassInfo.h"
#include "Kismet/GameplayStatics.h"
#include "Player/UhuPlayerState.h"
#include "UI/UhuHUD.h"
#include "UI/WidgetController/UhuWidgetController.h"

bool UUhuAbilitySystemLibrary::MakeWidgetControllerParams(const UObject* WorldContextObject, FWidgetControllerParams& OutWCParams, AUhuHUD*& OutUhuHUD)
{
	if (APlayerController* PC = UGameplayStatics::GetPlayerController(WorldContextObject, 0))
	{
		OutUhuHUD = Cast<AUhuHUD>(PC->GetHUD());
		if (OutUhuHUD)
		{
			AUhuPlayerState* PS = PC->GetPlayerState<AUhuPlayerState>();
			UAbilitySystemComponent* ASC = PS->GetAbilitySystemComponent();
			UAttributeSet* AS = PS->GetAttributeSet();

			OutWCParams.AttributeSet = AS;
			OutWCParams.AbilitySystemComponent = ASC;
			OutWCParams.PlayerState = PS;
			OutWCParams.PlayerController = PC;
			return true;
		}
	}
	return false;
}

UOverlayWidgetController* UUhuAbilitySystemLibrary::GetOverlayWidgetController(const UObject* WorldContextObject)
{
	FWidgetControllerParams WCParams;
	AUhuHUD* UhuHUD = nullptr;
	if (MakeWidgetControllerParams(WorldContextObject, WCParams, UhuHUD))
	{
		return UhuHUD->GetOverlayWidgetController(WCParams);
	}
	return nullptr;
}


void UUhuAbilitySystemLibrary::InitializeDefaultAttributes(const UObject* WorldContextObject, ECharacterClass CharacterClass, float Level, UAbilitySystemComponent* ASC)
{
	AActor* AvatarActor = ASC->GetAvatarActor();

	
	UCharacterClassInfo* CharacterClassInfo = GetCharacterClassInfo(WorldContextObject);
	FCharacterClassDefaultInfo ClassDefaultInfo = CharacterClassInfo->GetClassDefaultInfo(CharacterClass);
	
	FGameplayEffectContextHandle PrimaryAttributesContextHandle = ASC->MakeEffectContext();
	PrimaryAttributesContextHandle.AddSourceObject(AvatarActor);
	const FGameplayEffectSpecHandle PrimaryAttributesSpecHandle = ASC->MakeOutgoingSpec(ClassDefaultInfo.PrimaryAttributes, Level, PrimaryAttributesContextHandle);
	ASC->ApplyGameplayEffectSpecToSelf(*PrimaryAttributesSpecHandle.Data.Get());

	FGameplayEffectContextHandle SecondaryAttributesContextHandle = ASC->MakeEffectContext();
	SecondaryAttributesContextHandle.AddSourceObject(AvatarActor);
	const FGameplayEffectSpecHandle SecondaryAttributesSpecHandle = ASC->MakeOutgoingSpec(CharacterClassInfo->SecondaryAttributes, Level, SecondaryAttributesContextHandle);
	ASC->ApplyGameplayEffectSpecToSelf(*SecondaryAttributesSpecHandle.Data.Get());

	FGameplayEffectContextHandle VitalAttributesContextHandle = ASC->MakeEffectContext();
	VitalAttributesContextHandle.AddSourceObject(AvatarActor);
	const FGameplayEffectSpecHandle VitalAttributesSpecHandle = ASC->MakeOutgoingSpec(CharacterClassInfo->VitalAttributes, Level, VitalAttributesContextHandle);
	ASC->ApplyGameplayEffectSpecToSelf(*VitalAttributesSpecHandle.Data.Get());
}

void UUhuAbilitySystemLibrary::GiveStartupAbilities(const UObject* WorldContextObject, UAbilitySystemComponent* ASC, ECharacterClass CharacterClass)
{
	UCharacterClassInfo* CharacterClassInfo = GetCharacterClassInfo(WorldContextObject);
	if (CharacterClassInfo == nullptr) return;
	for (TSubclassOf<UGameplayAbility> AbilityClass : CharacterClassInfo->CommonAbilities)
	{
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(AbilityClass, 1);
		ASC->GiveAbility(AbilitySpec);
	}
	const FCharacterClassDefaultInfo& DefaultInfo = CharacterClassInfo->GetClassDefaultInfo(CharacterClass);
}

UCharacterClassInfo* UUhuAbilitySystemLibrary::GetCharacterClassInfo(const UObject* WorldContextObject)
{
	const AUhuSurvivalGameMode* UhuGameMode = Cast<AUhuSurvivalGameMode>(UGameplayStatics::GetGameMode(WorldContextObject));
	if (UhuGameMode == nullptr) return nullptr;
	return UhuGameMode->CharacterClassInfo;
}

UAbilityInfo* UUhuAbilitySystemLibrary::GetAbilityInfo(const UObject* WorldContextObject)
{
	const AUhuSurvivalGameMode* UhuGameMode = Cast<AUhuSurvivalGameMode>(UGameplayStatics::GetGameMode(WorldContextObject));
	if (UhuGameMode == nullptr) return nullptr;
	return UhuGameMode->AbilityInfo;
}
