// Fill out your copyright notice in the Description page of Project Settings.

#include "LobbyGameMode.h"
#include "TimerManager.h"

#include "Public/PuzzlePlatformsGameInstance.h"


void ALobbyGameMode::PostLogin(APlayerController* NewPlayer)
{
	UE_LOG(LogTemp, Warning, TEXT("[%s]"), *FString(__FUNCTION__));

	Super::PostLogin(NewPlayer);

	if (PlayersNumber < 5)
	{
		PlayersNumber++;

		GetWorldTimerManager().ClearTimer(TimerStartGame);
		GetWorldTimerManager().SetTimer(TimerStartGame, this, &ALobbyGameMode::StartGame, 10.f);

		UE_LOG(LogTemp, Warning, TEXT("Server contains %d players"), PlayersNumber);
	}

	if(PlayersNumber == 5)
	{
		UE_LOG(LogTemp, Warning, TEXT("Server is full"));

		StartGame();
	}
}

void ALobbyGameMode::Logout(AController * Exiting)
{
	Super::Logout(Exiting);

	--PlayersNumber;
}

void ALobbyGameMode::StartGame()
{
	auto GameInstance = Cast<UPuzzlePlatformsGameInstance>(GetGameInstance());
	if (!GameInstance)
	{
		return;
	}

	UE_LOG(LogTemp, Warning, TEXT("[%s]"), *FString(__FUNCTION__));

	UWorld* World = GetWorld();

	if (!ensure(World))
		return;

	GameInstance->StartSession();

	bUseSeamlessTravel = true;
	World->ServerTravel("/Game/PuzzlePlatforms/Maps/ThirdPersonExampleMap?listen");
}
