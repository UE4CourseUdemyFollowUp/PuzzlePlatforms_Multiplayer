// Fill out your copyright notice in the Description page of Project Settings.

#include "LobbyGameMode.h"


void ALobbyGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	if (PlayersNumber < 3)
	{
		PlayersNumber++;
		UE_LOG(LogTemp, Warning, TEXT("Server contains %d players"), PlayersNumber);
	}

	if(PlayersNumber == 3)
	{
		UE_LOG(LogTemp, Warning, TEXT("Server is full"));

		UWorld* World = GetWorld();

		if (!ensure(World))
			return;

		UE_LOG(LogTemp, Warning, TEXT("[%s]"), *FString(__FUNCTION__));

		bUseSeamlessTravel = true;
		World->ServerTravel("/Game/PuzzlePlatforms/Maps/ThirdPersonExampleMap?listen");
	}
}

void ALobbyGameMode::Logout(AController * Exiting)
{
	Super::Logout(Exiting);

	--PlayersNumber;
}
