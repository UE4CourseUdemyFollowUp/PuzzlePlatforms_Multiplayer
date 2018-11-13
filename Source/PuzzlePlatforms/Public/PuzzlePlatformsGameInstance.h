// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MenuSystem/MenuInterface.h"
#include "PuzzlePlatformsGameInstance.generated.h"

class UMenuWidget;

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMS_API UPuzzlePlatformsGameInstance : public UGameInstance, public IMenuInterface
{
	GENERATED_BODY()
	
public:
	UPuzzlePlatformsGameInstance(const FObjectInitializer & ObjectInitializer);
	virtual void Init() override;

	UFUNCTION(BlueprintCallable)
	void LoadMenu();

	UFUNCTION(BlueprintCallable)
	void LoadIngameMenu();

	UFUNCTION(Exec)
	void HostServer() override;

	UFUNCTION(Exec)
	void JoinGame(const FString& Address) override;

private:
	TSubclassOf<class UUserWidget> MenuClass;
	TSubclassOf<class UMenuWidget> IngameMenuClass;
	
	class UMainMenu* MainMenu;
};
