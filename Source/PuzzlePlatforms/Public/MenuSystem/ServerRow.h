// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ServerRow.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMS_API UServerRow : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* TextBlock_ServerName;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* TextBlock_HostName;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* TextBlock_PlayersCount;

	void Setup(class UMainMenu* InParent, uint32 InIndex);

	UPROPERTY(BlueprintReadOnly)
	bool Selected;

private:

	class UMainMenu * Parent;
	uint32 Index;

	UPROPERTY(meta = (BindWidget))
	class UButton* Button_ServerRow;
	
	UFUNCTION()
	void OnRowClicked();
	
};
