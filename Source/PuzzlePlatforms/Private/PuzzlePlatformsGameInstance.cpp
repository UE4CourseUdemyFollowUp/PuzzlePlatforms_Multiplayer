// Fill out your copyright notice in the Description page of Project Settings.

#include "PuzzlePlatformsGameInstance.h"
#include <Runtime/Engine/Classes/Engine/Engine.h>
#include "UObject/ConstructorHelpers.h"
#include "PlatformTrigger.h"
#include "Runtime/UMG/Public/Blueprint/UserWidget.h"
#include "MenuSystem/MainMenu.h"


UPuzzlePlatformsGameInstance::UPuzzlePlatformsGameInstance(const FObjectInitializer & ObjectInitializer)
{
	ConstructorHelpers::FClassFinder<UUserWidget> MainMenuBPClass(TEXT("/Game/MenuSystem/BP_MainMenu"));

	if (!ensure(MainMenuBPClass.Class != nullptr))
		return;

	MenuClass = MainMenuBPClass.Class;
	UE_LOG(LogTemp, Warning, TEXT("Found class %s"), *MainMenuBPClass.Class->GetName());
}

void UPuzzlePlatformsGameInstance::Init()
{
	Super::Init();
	UE_LOG(LogTemp, Warning, TEXT("GameInstance Init"));
}

void UPuzzlePlatformsGameInstance::LoadMenu()
{
	if (!ensure(MenuClass != nullptr))
		return;

	Menu = CreateWidget<UMainMenu>(this, MenuClass);

	if (!ensure(Menu != nullptr))
		return;

	Menu->Setup();
	Menu->SetMenuInterface(this);
	
}

void UPuzzlePlatformsGameInstance::HostServer()
{
	UE_LOG(LogTemp, Warning, TEXT("[%s]"), *FString(__FUNCTION__));
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


