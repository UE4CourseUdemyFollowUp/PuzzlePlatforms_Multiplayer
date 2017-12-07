// Fill out your copyright notice in the Description page of Project Settings.

#include "PuzzlePlatformsGameInstance.h"
#include <Runtime/Engine/Classes/Engine/Engine.h>

UPuzzlePlatformsGameInstance::UPuzzlePlatformsGameInstance(const FObjectInitializer & ObjectInitializer)
{
	UE_LOG(LogTemp, Warning, TEXT("GameInstance Constructor"));
}

void UPuzzlePlatformsGameInstance::Init()
{
	Super::Init();
	UE_LOG(LogTemp, Warning, TEXT("GameInstance Init"));
}

void UPuzzlePlatformsGameInstance::Host()
{
	UEngine* Engine = GetEngine();
	if (!ensure(Engine))
		return;

	Engine->AddOnScreenDebugMessage(0, 5.f, FColor::White, TEXT("Host!"));
	
	UWorld* World = GetWorld();

	if (!ensure(World))
		return;

	World->ServerTravel("/Game/ThirdPersonCPP/Maps/ThirdPersonExampleMap?listen");
}

void UPuzzlePlatformsGameInstance::Join(const FString & Address)
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


