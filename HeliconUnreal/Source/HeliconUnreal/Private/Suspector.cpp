// Fill out your copyright notice in the Description page of Project Settings.


#include "Suspector.h"

// Sets default values
ASuspector::ASuspector()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASuspector::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASuspector::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

