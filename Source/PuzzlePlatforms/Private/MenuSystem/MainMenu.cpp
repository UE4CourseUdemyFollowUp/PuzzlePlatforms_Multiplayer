// Fill out your copyright notice in the Description page of Project Settings.

#include "MainMenu.h"
#include "MenuInterface.h"
#include "MenuWidget.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Components/EditableTextBox.h"
#include "Engine/World.h"
#include "UObject/ConstructorHelpers.h"
#include "Public/MenuSystem/ServerRow.h"
#include "TextBlock.h"

UMainMenu::UMainMenu(const FObjectInitializer & ObjectInitializer)
{
	ConstructorHelpers::FClassFinder<UUserWidget> ServerRowBPClass(TEXT("/Game/MenuSystem/WBP_ServerRow"));

	if (!ensure(ServerRowBPClass.Class != nullptr))
		return;

	ServerRowClass = ServerRowBPClass.Class;
}

bool UMainMenu::Initialize()
{
	bool ret = Super::Initialize();

	if (!ret)
		return ret;

	if (!Button_Host)
		return false;
	Button_Host->OnClicked.AddDynamic(this, &UMainMenu::HostServer);

	if (!Button_JoinMenu)
		return false;
	Button_JoinMenu->OnClicked.AddDynamic(this, &UMainMenu::OpenJoinGameMenu);

	if (!Button_JoinGame)
		return false;
	Button_JoinGame->OnClicked.AddDynamic(this, &UMainMenu::JoinServer);

	if (!Button_CanselJoinMenu)
		return false;
	Button_CanselJoinMenu->OnClicked.AddDynamic(this, &UMainMenu::OpenMainMenu);

	if (!Button_Settings)
		return false;
	Button_Settings->OnClicked.AddDynamic(this, &UMainMenu::ShowSettings);

	if (!Button_Exit)
		return false;
	Button_Exit->OnClicked.AddDynamic(this, &UMainMenu::ExitGame);

	return true;
}

void UMainMenu::OpenJoinGameMenu()
{
	UE_LOG(LogTemp, Warning, TEXT("[%s]"), *FString(__FUNCTION__));
	if (!MenuSwitcher || !JoinMenu)
	{
		return;
	}
	MenuSwitcher->SetActiveWidget(JoinMenu);

	if (MenuInterface)
	{
		MenuInterface->RefreshServerList();
	}
}

void UMainMenu::OpenMainMenu()
{
	UE_LOG(LogTemp, Warning, TEXT("[%s]"), *FString(__FUNCTION__));
	if (!MenuSwitcher || !MainMenu)
	{
		return;
	}
	MenuSwitcher->SetActiveWidget(MainMenu);
}

void UMainMenu::HostServer()
{
	UE_LOG(LogTemp, Warning, TEXT("[%s]"), *FString(__FUNCTION__));

	if (!ensure(MenuInterface != nullptr))
		return;

	MenuInterface->HostServer();
}

void UMainMenu::SetServerList(TArray<FString> ServerNames)
{
	auto World = GetWorld();

	if (!World)
	{
		return;
	}

	ScrollBox_ServerList->ClearChildren();

	for (auto& ServerName : ServerNames)
	{
		UServerRow* ServerRow = CreateWidget<UServerRow>(World, ServerRowClass);

		if (!ensure(ServerRow != nullptr))
		{
			return;
		}

		ServerRow->TextBlock_ServerName->SetText(FText::FromString(ServerName));
		ScrollBox_ServerList->AddChild(ServerRow);
	}
}

void UMainMenu::JoinServer()
{
	UE_LOG(LogTemp, Warning, TEXT("[%s]"), *FString(__FUNCTION__));
	//if (!EditableTextBox_IPAddress || !MenuInterface)
	//	return;

	//const FString& IPAddress = EditableTextBox_IPAddress->GetText().ToString();

	//if (!IPAddress.IsEmpty())
	//{
	MenuInterface->JoinGame("");
	//}	

}


void UMainMenu::ShowSettings()
{
	UE_LOG(LogTemp, Warning, TEXT("[%s]"), *FString(__FUNCTION__));
}

void UMainMenu::ExitGame()
{
	UE_LOG(LogTemp, Warning, TEXT("[%s]"), *FString(__FUNCTION__));
	ExitGamePressed();
}




