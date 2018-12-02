// Fill out your copyright notice in the Description page of Project Settings.

#include "ServerRow.h"
#include "Public/MenuSystem/MainMenu.h"
#include "Components/Button.h"

void UServerRow::Setup(UMainMenu * InParent, uint32 InIndex)
{
	Parent = InParent;
	Index = InIndex;

	Button_ServerRow->OnClicked.AddDynamic(this, &UServerRow::OnRowClicked);
}

void UServerRow::OnRowClicked()
{
	if (Parent)
	{
		Parent->SetIndex(Index);
	}
}
