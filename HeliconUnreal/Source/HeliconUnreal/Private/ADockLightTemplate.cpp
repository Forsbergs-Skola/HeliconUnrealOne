// Fill out your copyright notice in the Description page of Project Settings.


#include "ADockLightTemplate.h"
#include "Kismet/GameplayStatics.h"
#include "DocksPuzzleManager.h"

// Sets default values
AADockLightTemplate::AADockLightTemplate()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	bIsLit = false;
	bPendingActivation = false;
	ActivationTimer = 0.f;
	GullPriority = 1.f;

}

// Called when the game starts or when spawned
void AADockLightTemplate::BeginPlay()
{
	Super::BeginPlay();
	PuzzleManager = Cast<ADocksPuzzleManager>(
		UGameplayStatics::GetActorOfClass(
			GetWorld(),
			ADocksPuzzleManager::StaticClass()
		)
	);

	UE_LOG(LogTemp, Warning, TEXT("Target sees manager: %s"),
		PuzzleManager ? TEXT("YES") : TEXT("NO"));
}

// Called every frame
void AADockLightTemplate::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AADockLightTemplate::LightOn()
{
	bIsLit = true;
	UE_LOG(LogTemp, Warning, TEXT("LIGHT ON: %s"), *GetName());
}

void AADockLightTemplate::LightOff()
{
	bIsLit = false;
	UE_LOG(LogTemp, Warning, TEXT("LIGHT OFF: %s"), *GetName());
}