// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "OnlineSubsystem.h"
#include "OnlineSessionInterface.h"
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
	void LoadMenuWidget();

	UFUNCTION(BlueprintCallable)
	void LoadIngameMenuWidget();

	UFUNCTION(Exec)
	void HostServer(FString ServerName) override;

	UFUNCTION(Exec)
	void JoinGame(const uint32& Index) override;

	void LoadMainMenu() override;

	void RefreshServerList() override;

	void StartSession();

private:
	TSubclassOf<class UUserWidget> MenuClass;
	TSubclassOf<class UMenuWidget> IngameMenuClass;
	
	class UMainMenu* MainMenu;

	FString DesiredServerName;

	IOnlineSessionPtr OnlineSession;

	TSharedPtr<class FOnlineSessionSearch> SessionSearch;

	void OnCreateSessionComplete(FName SessionName, bool Success);
	void OnDestroySessionComplete(FName SessionName, bool Success);
	void OnFindSessionComplete(bool Success);
	void OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result);

	void CreateSession();
	
};
