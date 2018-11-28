// Fill out your copyright notice in the Description page of Project Settings.

#include "PuzzlePlatformsGameInstance.h"
#include "Engine/Engine.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"
#include "OnlineSessionInterface.h"
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
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Found no subsystem"),);
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

void UPuzzlePlatformsGameInstance::JoinGame(const FString& Address)
{
	UEngine* Engine = GetEngine();
	if (!ensure(Engine))
		return;

	Engine->AddOnScreenDebugMessage(0, 5.f, FColor::White, FString::Printf(TEXT("Joining %s ..."), *Address));

	APlayerController* PlayerController = GetFirstLocalPlayerController();

	if (!ensure(PlayerController))
		return;

	PlayerController->ClientTravel(Address, ETravelType::TRAVEL_Absolute);
}

void UPuzzlePlatformsGameInstance::LoadMainMenu()
{
	UE_LOG(LogTemp, Warning, TEXT("[%s]"), *FString(__FUNCTION__));

	APlayerController* PlayerController = GetFirstLocalPlayerController();
	if (!ensure(PlayerController))
		return;

	PlayerController->ClientTravel("Game/MenuSystem/MainMenu", ETravelType::TRAVEL_Absolute);
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
	if (Success)
	{
		CreateSession();
	}
}

void UPuzzlePlatformsGameInstance::CreateSession()
{
	if (OnlineSession.IsValid())
	{
		FOnlineSessionSettings OnlineSessionSettings;
		OnlineSession->CreateSession(0, SESSION_NAME, OnlineSessionSettings);
	}
}


