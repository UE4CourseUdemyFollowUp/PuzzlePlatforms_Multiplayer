// Fill out your copyright notice in the Description page of Project Settings.

#include "MenuSystem/MenuWidget.h"
#include "MenuSystem/MenuInterface.h"
#include "Engine/World.h"

IMenuInterface * UMenuWidget::getMenuInterface() const
{
	return MenuInterface;
}

void UMenuWidget::SetMenuInterface(IMenuInterface* Interface)
{
	if (Interface == nullptr)
		return;

	MenuInterface = Interface;
}

void UMenuWidget::Setup()
{
	auto World = GetWorld();

	if (!World)
	{
		return;
	}

	APlayerController* PlayerController = World->GetFirstPlayerController();

	if (!ensure(PlayerController))
		return;

	FInputModeUIOnly InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeData.SetWidgetToFocus(this->TakeWidget());

	PlayerController->SetInputMode(InputModeData);

	PlayerController->bShowMouseCursor = true;

	this->AddToViewport();
}

void UMenuWidget::OnLevelRemovedFromWorld(ULevel * InLevel, UWorld * InWorld)
{
	UE_LOG(LogTemp, Warning, TEXT("[%s]"), *FString(__FUNCTION__));
	Super::OnLevelRemovedFromWorld(InLevel, InWorld);

	auto World = GetWorld();

	if (!World)
	{
		return;
	}

	APlayerController* PlayerController = World->GetFirstPlayerController();

	if (!ensure(PlayerController))
		return;

	FInputModeGameOnly InputModeData;
	PlayerController->SetInputMode(InputModeData);
	PlayerController->bShowMouseCursor = false;


	this->RemoveFromViewport();
}

void UMenuWidget::ExitGamePressed()
{
	auto World = GetWorld();

	if (!World)
	{
		return;
	}

	APlayerController* PlayerController = World->GetFirstPlayerController();

	if (PlayerController)
	{
		PlayerController->ConsoleCommand(FString("quit"));
	}
}
