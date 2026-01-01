// Fill out your copyright notice in the Description page of Project Settings.


#include "Menu.h"

void UMenu::MenuSetup()
{
	AddToViewport();
	SetVisibility(ESlateVisibility::Visible);
	SetIsFocusable(true);

	UWorld* World = GetWorld();
	if (World)
	{
		APlayerController* PlayerController = World->GetFirstPlayerController();
		if (PlayerController)
		{
			FInputModeUIOnly InputModeDate;
			InputModeDate.SetWidgetToFocus(TakeWidget());
			InputModeDate.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
			PlayerController->SetInputMode(InputModeDate);
			PlayerController->bShowMouseCursor = true;
		}
	}
}
