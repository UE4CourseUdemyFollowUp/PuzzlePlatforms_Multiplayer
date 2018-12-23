// Fill out your copyright notice in the Description page of Project Settings.

#include "LobbyGameMode.h"


void ALobbyGameMode::PostLogin(APlayerController* NewPlayer)
{
	if (PlayersNumber < 3)
	{
		PlayersNumber++;
		UE_LOG(LogTemp, Warning, TEXT("Server contains %d players"), PlayersNumber);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Server is full"));
	}
}






