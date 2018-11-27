// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MenuSystem/MenuWidget.h"
#include "IngameMenu.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMS_API UIngameMenu : public UMenuWidget
{
	GENERATED_BODY()
	
protected:
	virtual bool Initialize() override;

private:

	UFUNCTION()
	void ReturnToGame();

	UFUNCTION()
	void QuitToMenu();

	UFUNCTION()
	void OpenSettings();

	UFUNCTION()
	void ExitGame();

	UPROPERTY(meta = (BindWidget))
	class UButton* Button_Return;

	UPROPERTY(meta = (BindWidget))
	class UButton* Button_Menu;

	UPROPERTY(meta = (BindWidget))
	class UButton* Button_Settings;

	UPROPERTY(meta = (BindWidget))
	class UButton* Button_Exit;
	
	
};
