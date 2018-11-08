// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenu.generated.h"

class IMenuInterface;

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMS_API UMainMenu : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetMenuInterface(IMenuInterface* Interface);
	IMenuInterface* getMenuInterface() const;

	void Setup();

protected:
	virtual bool Initialize() override;

private:
	UFUNCTION()
	void JoinGame();

	UFUNCTION()
	void HostServer();

	UFUNCTION()
	void ShowSettings();

	UFUNCTION()
	void ExitGame();
	
	UPROPERTY(meta = (BindWidget))
	class UButton* Button_Host;

	UPROPERTY(meta = (BindWidget))
	class UButton* Button_Join;

	UPROPERTY(meta = (BindWidget))
	class UButton* Button_Settings;

	UPROPERTY(meta = (BindWidget))
	class UButton* Button_Exit;

	IMenuInterface* MenuInterface;	
};
