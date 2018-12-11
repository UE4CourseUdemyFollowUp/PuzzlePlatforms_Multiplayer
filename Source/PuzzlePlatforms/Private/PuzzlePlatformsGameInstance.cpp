// Fill out your copyright notice in the Description page of Project Settings.

#include "PuzzlePlatformsGameInstance.h"
#include "Engine/Engine.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"
#include "OnlineSessionSettings.h"

#include "PlatformTrigger.h"
#include "MenuSystem/MainMenu.h"
#include "MenuSystem/MenuWidget.h"

const static FName SESSION_NAME = TEXT("My Session");

UPuzzlePlatformsGameInstance::UPuzzlePlatformsGameInstance(const FObjectInitializer & ObjectInitializer)
{
	ConstructorHelpers::FClassFinder<UMainMenu> MainMenuBPClass(TEXT("/Game/MenuSystem/WBP_MainMenu"));

	if (!ensure(MainMenuBPClass.Class != nullptr))
		return;

	MenuClass = MainMenuBPClass.Class;

	ConstructorHelpers::FClassFinder<UUserWidget> IngameMenuBPClass(TEXT("/Game/MenuSystem/WBP_IngameMenu"));

	if (!ensure(IngameMenuBPClass.Class != nullptr))
		return;

	IngameMenuClass = IngameMenuBPClass.Class;

	UE_LOG(LogTemp, Warning, TEXT("Found class %s"), *MainMenuBPClass.Class->GetName());
	UE_LOG(LogTemp, Warning, TEXT("Found class %s"), *IngameMenuBPClass.Class->GetName());
}

void UPuzzlePlatformsGameInstance::Init()
{
	Super::Init();

	IOnlineSubsystem* Subsystem = IOnlineSubsystem::Get();

	if (Subsystem)
	{
		UE_LOG(LogTemp, Warning, TEXT("Found subsystem interface: %s"), *Subsystem->GetSubsystemName().ToString());
		OnlineSession = Subsystem->GetSessionInterface();
		if (OnlineSession.IsValid())
		{
			UE_LOG(LogTemp, Warning, TEXT("Found system interface"));
			OnlineSession->OnCreateSessionCompleteDelegates.AddUObject(this, &UPuzzlePlatformsGameInstance::OnCreateSessionComplete);
			OnlineSession->OnDestroySessionCompleteDelegates.AddUObject(this, &UPuzzlePlatformsGameInstance::OnDestroySessionComplete);		
			OnlineSession->OnFindSessionsCompleteDelegates.AddUObject(this, &UPuzzlePlatformsGameInstance::OnFindSessionComplete);
			OnlineSession->OnJoinSessionCompleteDelegates.AddUObject(this, &UPuzzlePlatformsGameInstance::OnJoinSessionComplete);
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Found no subsystem"));
	}
}

void UPuzzlePlatformsGameInstance::LoadMenuWidget()
{
	if (!ensure(MenuClass != nullptr))
		return;

	MainMenu = CreateWidget<UMainMenu>(this, MenuClass);

	if (!ensure(MainMenu != nullptr))
		return;

	MainMenu->Setup();
	MainMenu->SetMenuInterface(this);
	
}

void UPuzzlePlatformsGameInstance::LoadIngameMenuWidget()
{
	if (!ensure(IngameMenuClass != nullptr))
		return;

	UMenuWidget* IngameMenu = CreateWidget<UMenuWidget>(this, IngameMenuClass);

	if (!ensure(IngameMenu != nullptr))
		return;

	IngameMenu->Setup();
	IngameMenu->SetMenuInterface(this);
}

void UPuzzlePlatformsGameInstance::HostServer()
{
	if (OnlineSession.IsValid())
	{
		if (OnlineSession->GetNamedSession(SESSION_NAME))
		{
			OnlineSession->DestroySession(SESSION_NAME);
		}
		else
		{
			CreateSession();
		}
	}
}

void UPuzzlePlatformsGameInstance::JoinGame(const uint32& Index)
{
	UE_LOG(LogTemp, Warning, TEXT("[%s]"), *FString(__FUNCTION__));
	if (OnlineSession.IsValid() && SessionSearch.IsValid())
	{
		OnlineSession->JoinSession(0, SESSION_NAME, SessionSearch->SearchResults[Index]);
	}
}

void UPuzzlePlatformsGameInstance::LoadMainMenu()
{
	UE_LOG(LogTemp, Warning, TEXT("[%s]"), *FString(__FUNCTION__));

	APlayerController* PlayerController = GetFirstLocalPlayerController();
	if (!ensure(PlayerController))
		return;

	PlayerController->ClientTravel("Game/MenuSystem/MainMenu", ETravelType::TRAVEL_Absolute);
}

void UPuzzlePlatformsGameInstance::RefreshServerList()
{
	SessionSearch = MakeShareable(new FOnlineSessionSearch());
	if (SessionSearch.IsValid())
	{
		//SessionSearch->bIsLanQuery = true;
		SessionSearch->MaxSearchResults = 1000;
		SessionSearch->QuerySettings.Set(SEARCH_PRESENCE, true, EOnlineComparisonOp::Type::Equals);
		UE_LOG(LogTemp, Warning, TEXT("Sessin search started"));
		OnlineSession->FindSessions(0, SessionSearch.ToSharedRef());
	}
}

void UPuzzlePlatformsGameInstance::OnCreateSessionComplete(FName SessionName, bool Success)
{
	UE_LOG(LogTemp, Warning, TEXT("[%s]"), *FString(__FUNCTION__));
	
	if (!Success)
	{
		UE_LOG(LogTemp, Warning, TEXT("Could Not Create A Session"));
		return;
	}
	UE_LOG(LogTemp, Warning, TEXT("Session Created"));
	
	UEngine* Engine = GetEngine();
	if (!ensure(Engine))
		return;

	Engine->AddOnScreenDebugMessage(0, 5.f, FColor::White, TEXT("Host!"));

	UWorld* World = GetWorld();

	if (!ensure(World))
		return;

	UE_LOG(LogTemp, Warning, TEXT("[%s]"), *FString(__FUNCTION__));

	World->ServerTravel("/Game/ThirdPersonCPP/Maps/ThirdPersonExampleMap?listen");
}

void UPuzzlePlatformsGameInstance::OnDestroySessionComplete(FName SessionName, bool Success)
{
	UE_LOG(LogTemp, Warning, TEXT("[%s]"), *FString(__FUNCTION__));
	if (Success)
	{
		CreateSession();
	}
}

void UPuzzlePlatformsGameInstance::OnFindSessionComplete(bool Success)
{
	if (Success && SessionSearch.IsValid() && MainMenu)
	{
		UE_LOG(LogTemp, Warning, TEXT("Sessin search eded"));

		TArray<FServerData> ServerIDs;
		for (auto& result : SessionSearch->SearchResults)
		{
			UE_LOG(LogTemp, Warning, TEXT("Sessin found ID: %s"), *(result.GetSessionIdStr()));
			FServerData ServerData;
			ServerData.Name = result.GetSessionIdStr();
			ServerData.MaxPlayers = result.Session.NumOpenPublicConnections;
			ServerData.CurrentPlayers = result.Session.SessionSettings.NumPublicConnections;
			ServerData.HostUsername = result.Session.OwningUserName;
			ServerIDs.Add(ServerData);
		}
		MainMenu->SetServerList(ServerIDs);
	}
}

void UPuzzlePlatformsGameInstance::OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result)
{
	UE_LOG(LogTemp, Warning, TEXT("[%s]"), *FString(__FUNCTION__));
	if (!OnlineSession.IsValid() && !EOnJoinSessionCompleteResult::Type::Success)
	{
		return;
	}

	FString AddressURL;
	if (!OnlineSession->GetResolvedConnectString(SESSION_NAME, AddressURL))
	{
		UE_LOG(LogTemp, Warning, TEXT("Could not receive the session address"));
		return;
	}

	UWorld* World = GetWorld();

	if (World)
	{
		APlayerController* PlayerController = World->GetFirstPlayerController();
		if (PlayerController)
		{
			PlayerController->ClientTravel(AddressURL, ETravelType::TRAVEL_Absolute);
		}	
	}	
}

void UPuzzlePlatformsGameInstance::CreateSession()
{
	if (OnlineSession.IsValid())
	{
		FOnlineSessionSettings OnlineSessionSettings;
		if (IOnlineSubsystem::Get()->GetSubsystemName() == "NULL")
		{
			OnlineSessionSettings.bIsLANMatch = true;
		}
		else
		{
			OnlineSessionSettings.bIsLANMatch = false;
		}

		OnlineSessionSettings.bAllowInvites = true;		
		OnlineSessionSettings.bShouldAdvertise = true;
		OnlineSessionSettings.NumPublicConnections = 2;
		OnlineSessionSettings.bUsesPresence = true;
		OnlineSession->CreateSession(0, SESSION_NAME, OnlineSessionSettings);
	}
}


