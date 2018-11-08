// Fill out your copyright notice in the Description page of Project Settings.

#include "MainMenu.h"
#include "MenuInterface.h"
#include "Components/Button.h"
#include "Engine/World.h"


bool UMainMenu::Initialize()
{
	bool ret = Super::Initialize();

	if (!ret)
		return ret;

	if (!Button_Host)
		return false;
	Button_Host->OnClicked.AddDynamic(this, &UMainMenu::HostServer);

	if (!Button_Join)
		return false;
	Button_Join->OnClicked.AddDynamic(this, &UMainMenu::JoinGame);

	if (!Button_Settings)
		return false;
	Button_Settings->OnClicked.AddDynamic(this, &UMainMenu::ShowSettings);

	if (!Button_Exit)
		return false;
	Button_Exit->OnClicked.AddDynamic(this, &UMainMenu::ExitGame);

	return true;
}

void UMainMenu::SetMenuInterface(IMenuInterface* Interface)
{
	if (Interface == nullptr)
		return;

	MenuInterface = Interface;
}

IMenuInterface* UMainMenu::getMenuInterface() const
{
	return MenuInterface;
}

void UMainMenu::Setup()
{
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();

	if (!ensure(PlayerController))
		return;

	FInputModeUIOnly InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeData.SetWidgetToFocus(this->TakeWidget());

	PlayerController->SetInputMode(InputModeData);

	PlayerController->bShowMouseCursor = true;

	this->AddToViewport();
}

void UMainMenu::JoinGame()
{
	UE_LOG(LogTemp, Warning, TEXT("UMainMenu::JoinServer"));
}

void UMainMenu::HostServer()
{
	UE_LOG(LogTemp, Warning, TEXT("UMainMenu::HostServer"));

	if (!ensure(MenuInterface != nullptr))
		return;

	MenuInterface->HostServer();
}


void UMainMenu::ShowSettings()
{
	UE_LOG(LogTemp, Warning, TEXT("UMainMenu::ShowSettings"));
}

void UMainMenu::ExitGame()
{
	UE_LOG(LogTemp, Warning, TEXT("UMainMenu::ExitGame"));
}




