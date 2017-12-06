// Fill out your copyright notice in the Description page of Project Settings.

#include "MovingPlatform.h"



AMovingPlatform::AMovingPlatform()
{
	PrimaryActorTick.bCanEverTick = true;
	SetMobility(EComponentMobility::Movable);
}

void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority())
	{
		SetReplicates(true);
		SetReplicateMovement(true);
	}
	GlobalTargetLocation = GetTransform().TransformPosition(TargetLocation);
	GlobalStartLocation = GetActorLocation();
}

void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (HasAuthority())
	{
		FVector ActorLocation = GetActorLocation();
		float TotalRouteLength = (GlobalStartLocation - GlobalTargetLocation).Size();
		float CurrentPathLength = (ActorLocation - GlobalStartLocation).Size();

		if (CurrentPathLength >= TotalRouteLength)
		{
			FVector SwapVector = GlobalStartLocation;
			GlobalStartLocation = GlobalTargetLocation;
			GlobalTargetLocation = SwapVector;
		}

		FVector Direction = (GlobalTargetLocation - GlobalStartLocation).GetSafeNormal();
		ActorLocation += Direction * MovementSpeed * DeltaTime;
		SetActorLocation(ActorLocation);
	}
}



