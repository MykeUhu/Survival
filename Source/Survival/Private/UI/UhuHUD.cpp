// UhuHUD.cpp
// Copyright by MykeUhu

#include "UI/UhuHUD.h"
#include "Blueprint/UserWidget.h"

AUhuHUD::AUhuHUD()
{
}

void AUhuHUD::BeginPlay()
{
	Super::BeginPlay();

	if (MainUIClass)
	{
		MainUIWidget = CreateWidget<UUserWidget>(GetOwningPlayerController(), MainUIClass);
		if (MainUIWidget)
		{
			MainUIWidget->AddToViewport();
			CreateMainUI();
		}
	}
}

