// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "MovingPlatform.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMS_API AMovingPlatform : public AStaticMeshActor
{
	GENERATED_BODY()
	
public:
	AMovingPlatform();

	void AddActiveTriggers();
	void RemoveActiveTriggers();

protected:
	virtual void Tick(float DeltaTime) override;
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditAnywhere, Category = "Movement")
	float MovementSpeed = 15;

	// To create a FVector widget, it has local transforms
	UPROPERTY(EditAnywhere, Category = "Movement", Meta = (MakeEditWidget = true))
	FVector TargetLocation;
	
	UPROPERTY(EditAnywhere)
	FVector GlobalTargetLocation;

	UPROPERTY(EditAnywhere)
	FVector GlobalStartLocation;

	UPROPERTY(EditAnywhere)
	int32 ActiveTriggersNum = 1;
};
