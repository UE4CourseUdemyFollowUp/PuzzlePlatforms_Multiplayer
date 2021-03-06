// Fill out your copyright notice in the Description page of Project Settings.

#include "PlatformTrigger.h"
#include "MovingPlatform.h"
#include "Runtime/Engine/Classes/Components/BoxComponent.h"


// Sets default values
APlatformTrigger::APlatformTrigger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TriggerVolume = CreateDefaultSubobject<UBoxComponent>(FName("TriggerVolume"));

	if (!ensure(TriggerVolume))
		return;

	SetRootComponent(TriggerVolume);
	TriggerVolume->OnComponentBeginOverlap.AddDynamic(this, &APlatformTrigger::OnOverlapBegin);
	TriggerVolume->OnComponentEndOverlap.AddDynamic(this, &APlatformTrigger::OnOverlapEnd);
}

// Called when the game starts or when spawned
void APlatformTrigger::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlatformTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APlatformTrigger::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("APlatformTrigger::OnOverlapBegin with %s "), *OtherComp->GetName());
	for (AMovingPlatform* Platform : PlatformsToTrigger)
	{
		Platform->AddActiveTriggers();
	}
}

void APlatformTrigger::OnOverlapEnd(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{
	UE_LOG(LogTemp, Warning, TEXT("APlatformTrigger::OnOverlapEnd"));
	for (AMovingPlatform* Platform : PlatformsToTrigger)
	{
		Platform->RemoveActiveTriggers();
	}
}

