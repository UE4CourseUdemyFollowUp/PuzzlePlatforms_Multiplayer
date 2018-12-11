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

void UMainMenu::SetServerList(TArray<FServerData> ServersData)
{
	auto World = GetWorld();

	if (!World)
	{
		return;
	}

	ScrollBox_ServerList->ClearChildren();

	uint32 Index = 0;
	for (auto& ServerData : ServersData)
	{
		UServerRow* ServerRow = CreateWidget<UServerRow>(World, ServerRowClass);

		if (!ensure(ServerRow != nullptr))
		{
			return;
		}

		//ServerRow->TextBlock_ServerName->SetText(FText::FromString(ServerData.Name));
		//ServerRow->TextBlock_HostName->SetText(FText::FromString(ServerData.HostUsername));
		ServerRow->TextBlock_PlayersCount->SetText(FText::FromString(FString::Printf(TEXT("%d/%d"), ServerData.CurrentPlayers, ServerData.MaxPlayers)));

		ServerRow->Setup(this, Index++);
		ScrollBox_ServerList->AddChild(ServerRow);
	}
}

void UMainMenu::SetIndex(uint32 Index)
{
	SelectedIndex = Index;
	UpdateChildren();
}

void UMainMenu::JoinServer()
{
	UE_LOG(LogTemp, Warning, TEXT("[%s]"), *FString(__FUNCTION__));
	if (SelectedIndex.IsSet() && MenuInterface)
	{
		MenuInterface->JoinGame(SelectedIndex.GetValue());
	}
	//if (!EditableTextBox_IPAddress || !MenuInterface)
	//	return;

	//const FString& IPAddress = EditableTextBox_IPAddress->GetText().ToString();

	//if (!IPAddress.IsEmpty())
	//{
	
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

void UMainMenu::UpdateChildren()
{
	auto ChildrenCount = ScrollBox_ServerList->GetChildrenCount();
	if (SelectedIndex.IsSet())
	{
		auto Index = SelectedIndex.GetValue();
		for (int32 i = 0; i < ChildrenCount; i++)
		{
			UServerRow* Child = Cast<UServerRow>(ScrollBox_ServerList->GetChildAt(i));

			if (Child)
			{
				Child->Selected = (Index == i);
			}
		}
	}
}




