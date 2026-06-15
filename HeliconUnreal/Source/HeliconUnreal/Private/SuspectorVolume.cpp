// Fill out your copyright notice in the Description page of Project Settings.


#include "SuspectorVolume.h"

// Sets default values
ASuspectorVolume::ASuspectorVolume()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASuspectorVolume::BeginPlay()
{
	Super::BeginPlay();
	SuspectorVolumeScale = GetActorScale();
	
}

// Called every frame
void ASuspectorVolume::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

