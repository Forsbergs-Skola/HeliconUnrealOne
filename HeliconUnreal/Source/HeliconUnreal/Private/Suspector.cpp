// Fill out your copyright notice in the Description page of Project Settings.

#include "Suspector.h"
#include "CPP_HeliconGameInstance.h"
#include "Engine/Engine.h"


// Sets default values
ASuspector::ASuspector()
{
	PrimaryActorTick.bCanEverTick = true;
	
}

void ASuspector::BeginPlay()
{
	Super::BeginPlay();
	
	UCPP_HeliconGameInstance* GameInstance = Cast<UCPP_HeliconGameInstance>(GetWorld()->GetGameInstance());
	
	if (GameInstance)
	{
		GameInstance->EventRelay->OnPuzzleCompleted.AddDynamic(this, &ASuspector::ExecuteSuspectBehaviour);
	}
}

void ASuspector::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASuspector::ExecuteSuspectBehaviour(FEventTagsStruct TagsStruct) 
{
	if (TagsStruct.TagsList.Contains("COMPLETED_PUZZLES"))
	{
		UE_LOG(LogTemp, Error, TEXT("Suspects completed puzzles"));
	}
}

