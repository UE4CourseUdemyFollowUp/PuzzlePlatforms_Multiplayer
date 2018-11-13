// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MenuSystem/MenuWidget.h"
#include "MainMenu.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMS_API UMainMenu : public UMenuWidget
{
	GENERATED_BODY()

protected:
	virtual bool Initialize() override;

private:
	UFUNCTION()
	void OpenJoinGameMenu();

	UFUNCTION()
	void OpenMainMenu();

	UFUNCTION()
	void HostServer();

	UFUNCTION()
	void JoinServer();

	UFUNCTION()
	void ShowSettings();

	UFUNCTION()
	void ExitGame();
	
	UPROPERTY(meta = (BindWidget))
	class UButton* Button_Host;

	UPROPERTY(meta = (BindWidget))
	class UButton* Button_JoinMenu;

	UPROPERTY(meta = (BindWidget))
	class UButton* Button_JoinGame;

	UPROPERTY(meta = (BindWidget))
	class UButton* Button_CanselJoinMenu;

	UPROPERTY(meta = (BindWidget))
	class UButton* Button_Settings;

	UPROPERTY(meta = (BindWidget))
	class UButton* Button_Exit;

	UPROPERTY(meta = (BindWidget))
	class UWidgetSwitcher* MenuSwitcher;

	UPROPERTY(meta = (BindWidget))
	class UWidget* JoinMenu;

	UPROPERTY(meta = (BindWidget))
	class UWidget* MainMenu;

	UPROPERTY(meta = (BindWidget))
	class UEditableTextBox* EditableTextBox_IPAddress;
};
