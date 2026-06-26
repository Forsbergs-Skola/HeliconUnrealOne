// Fill out your copyright notice in the Description page of Project Settings.


#include "DocksPuzzleManager.h"

#include "GullActor.h"

// Sets default values
ADocksPuzzleManager::ADocksPuzzleManager()
{
	PrimaryActorTick.bCanEverTick = false;

	CurrentTurn = EDocksPuzzleTurn::Player;
	bPuzzleComplete = false;

}

// Called when the game starts or when spawned
void ADocksPuzzleManager::BeginPlay()
{
	Super::BeginPlay();
	StartPlayerTurn();
}

void ADocksPuzzleManager::StartPlayerTurn()
{
	if (bPuzzleComplete)
	{
		return;
	}

	CurrentTurn = EDocksPuzzleTurn::Player;
	BP_PlayerTurnStarted();

	UE_LOG(LogTemp, Warning,
		TEXT("Player Turn Started"));
}

void ADocksPuzzleManager::EndPlayerTurn()
{
	if (CurrentTurn != EDocksPuzzleTurn::Player)
	{
		return;
	}

	StartGullTurn();
}

void ADocksPuzzleManager::StartGullTurn()
{
	CurrentTurn = EDocksPuzzleTurn::Gulls;
	BP_GullTurnStarted();

	UE_LOG(LogTemp, Warning,
		TEXT("Gull Turn Started"));

	for (AGullActor* Gull : Gulls)
	{
		if (Gull)
		{
			Gull->StartTurn(PuzzleLights);
		}
	}
}

void ADocksPuzzleManager::EndGullTurn()
{
	if (CurrentTurn != EDocksPuzzleTurn::Gulls)
	{
		return;
	}

	CheckWinCondition();

	if (!bPuzzleComplete)
	{
		StartPlayerTurn();
	}
}

void ADocksPuzzleManager::CheckWinCondition()
{
}

void ADocksPuzzleManager::ResetPuzzle()
{
	CurrentTurn = EDocksPuzzleTurn::Player;
	bPuzzleComplete = false;

	StartPlayerTurn();
}