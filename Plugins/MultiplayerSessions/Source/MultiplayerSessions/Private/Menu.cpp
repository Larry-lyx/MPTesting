// Fill out your copyright notice in the Description page of Project Settings.


#include "Menu.h"
#include "OnlineSessionSettings.h"
#include "MultiplayerSessionsSubsystem.h"
#include "Components/Button.h"

void UMenu::MenuSetup(int32 NumberOfPublicConnections , FString TypeOfMatch )
{
	NumPublicConnections = NumberOfPublicConnections;
	MatchType = TypeOfMatch;
	
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

	UGameInstance* GameInstance = GetGameInstance();
	if (GameInstance)
	{
		MultiplayerSessionSubsystem = GameInstance->GetSubsystem<UMultiplayerSessionsSubsystem>();
	}

	if (MultiplayerSessionSubsystem)
	{
		MultiplayerSessionSubsystem->MultiPlayerOnCreateSessionComplete.AddDynamic(this , &ThisClass::OnCreateSession);
		MultiplayerSessionSubsystem->MultiPlayerOnFindSessionsComplete.AddUObject(this , &ThisClass::OnFindSessions);
		MultiplayerSessionSubsystem->MultiPlayerOnJoinSessionComplete.AddUObject(this , &ThisClass::OnJoinSession);
		MultiplayerSessionSubsystem->MultiPlayerOnDestroySessionComplete.AddDynamic(this , &ThisClass::OnDestroySession);
		MultiplayerSessionSubsystem->MultiPlayerOnStartSessionComplete.AddDynamic(this , &ThisClass::OnStarSession);
	}
}

bool UMenu::Initialize()
{
	if (!Super::Initialize())
	{
		return false;
	}

	if (HostButton)
	{
		HostButton->OnClicked.AddDynamic(this , &ThisClass::HostButtonClicked);
	}

	if (JoinButton)
	{
		JoinButton->OnClicked.AddDynamic(this, &ThisClass::JoinButtonClicked);
	}
	
	return true;
}

void UMenu::NativeDestruct()
{
	MenuTearDown();
	Super::NativeDestruct();
}

void UMenu::OnCreateSession(bool bWasSuccessful)
{
	if (bWasSuccessful)
	{
		GEngine->AddOnScreenDebugMessage(
			-1 ,
			15.f ,
			FColor::Green ,
			FString(TEXT("Session created Successfully")));

		UWorld* World = GetWorld();
		if (World)
		{
			World->ServerTravel("/Game/ThirdPerson/Lobby?listen");
		}
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(
			-1 ,
			15.f ,
			FColor::Red ,
			FString(TEXT("Failed to Create Session!")));
	}
}

void UMenu::OnFindSessions(const TArray<FOnlineSessionSearchResult>& SessionResults, bool bWasSuccessful)
{
	if (MultiplayerSessionSubsystem == nullptr) return;
	
	for (auto Result : SessionResults)
	{
		FString SettingValue;
		Result.Session.SessionSettings.Get(FName("MatchType"), SettingValue);

		if (SettingValue == MatchType)
		{
			MultiplayerSessionSubsystem->JoinSession(Result);
			return;
		}
	}
}

void UMenu::OnJoinSession(EOnJoinSessionCompleteResult::Type)
{
	IOnlineSubsystem* Subsystem = IOnlineSubsystem::Get();
	if (Subsystem)
	{
		IOnlineSessionPtr SessionInterface = Subsystem->GetSessionInterface();

		if (SessionInterface.IsValid())
		{
			FString Address;
			SessionInterface->GetResolvedConnectString(NAME_GameSession , Address);
			
			APlayerController* PlayerController = GetGameInstance()->GetFirstLocalPlayerController();
			if (PlayerController)
			{
				PlayerController->ClientTravel(Address, ETravelType::TRAVEL_Absolute);
			}
		}
	}
}

void UMenu::OnDestroySession(bool bWasSuccessful)
{
}

void UMenu::OnStarSession(bool bWasSuccessful)
{
}

void UMenu::HostButtonClicked()
{
	if (MultiplayerSessionSubsystem)
	{
		MultiplayerSessionSubsystem->CreateSession(NumPublicConnections , MatchType);
	}
}

void UMenu::JoinButtonClicked()
{
	if (MultiplayerSessionSubsystem)
	{
		MultiplayerSessionSubsystem->FindSessions(10000);
	}
}

void UMenu::MenuTearDown()
{
	RemoveFromParent();
	UWorld* World = GetWorld();
	if (World)
	{
		APlayerController* PlayerController = World->GetFirstPlayerController();
		if (PlayerController)
		{
			FInputModeGameOnly InputModeData;
			PlayerController->SetInputMode(InputModeData);
			PlayerController->bShowMouseCursor = false;
		}
	}
}
