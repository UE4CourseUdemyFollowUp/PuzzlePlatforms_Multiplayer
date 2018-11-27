// Fill out your copyright notice in the Description page of Project Settings.

#include "IngameMenu.h"
#include "MenuInterface.h"
#include "Components/Button.h"




bool UIngameMenu::Initialize()
{
	bool result = Super::Initialize();
	
	if (!Button_Return)
		return false;
	Button_Return->OnClicked.AddDynamic(this, &UIngameMenu::ReturnToGame);

	if (!Button_Menu)
		return false;
	Button_Menu->OnClicked.AddDynamic(this, &UIngameMenu::QuitToMenu);

	if (!Button_Settings)
		return false;
	Button_Settings->OnClicked.AddDynamic(this, &UIngameMenu::OpenSettings);

	if (!Button_Exit)
		return false;
	Button_Exit->OnClicked.AddDynamic(this, &UIngameMenu::ExitGame);


	return result;
}

void UIngameMenu::ReturnToGame()
{
	UE_LOG(LogTemp, Warning, TEXT("[%s]"), *FString(__FUNCTION__));
	OnLevelRemovedFromWorld(nullptr, nullptr);
}

void UIngameMenu::QuitToMenu()
{
	UE_LOG(LogTemp, Warning, TEXT("[%s]"), *FString(__FUNCTION__));
	Super::OnLevelRemovedFromWorld(nullptr, nullptr);

	if (MenuInterface)
	{		
		MenuInterface->LoadMainMenu();
	}
}

void UIngameMenu::OpenSettings()
{
	UE_LOG(LogTemp, Warning, TEXT("[%s]"), *FString(__FUNCTION__));
}

void UIngameMenu::ExitGame()
{
	UE_LOG(LogTemp, Warning, TEXT("[%s]"), *FString(__FUNCTION__));
	ExitGamePressed();
}
