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

	void Setup(class UMainMenu* InParent, uint32 InIndex);

private:

	class UMainMenu * Parent;
	uint32 Index;

	UPROPERTY(meta = (BindWidget))
	class UButton* Button_ServerRow;
	
	UFUNCTION()
	void OnRowClicked();
	
};
