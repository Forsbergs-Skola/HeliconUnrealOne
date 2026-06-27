#include "DocksPuzzleManager.h"
#include "ADockLightTemplate.h"
#include "AGullRestPoint.h"
#include "GullActor.h"
#include "SpotlightActor.h"
#include "Kismet/GameplayStatics.h"

ADocksPuzzleManager::ADocksPuzzleManager()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ADocksPuzzleManager::BeginPlay()
{
	Super::BeginPlay();
	RegisterPuzzleActors();
	GatherRestPointsIfNeeded();
	GatherSpotlightsIfNeeded();
	StartPlayerTurn();
}

void ADocksPuzzleManager::RegisterPuzzleActors()
{
	for (AADockLightTemplate* Light : PuzzleLights)
	{
		if (Light)
		{
			Light->RegisterPuzzleManager(this);
		}
	}

	for (ASpotlightActor* Spotlight : Spotlights)
	{
		if (Spotlight)
		{
			Spotlight->RegisterPuzzleManager(this);
		}
	}
}

void ADocksPuzzleManager::GatherRestPointsIfNeeded()
{
	if (RestPoints.Num() > 0)
	{
		return;
	}

	TArray<AActor*> FoundRestPoints;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AGullRestPoint::StaticClass(), FoundRestPoints);

	RestPoints.Reserve(FoundRestPoints.Num());
	for (AActor* Actor : FoundRestPoints)
	{
		if (AGullRestPoint* RestPoint = Cast<AGullRestPoint>(Actor))
		{
			RestPoints.Add(RestPoint);
		}
	}
}

void ADocksPuzzleManager::GatherSpotlightsIfNeeded()
{
	if (Spotlights.Num() > 0)
	{
		return;
	}

	TArray<AActor*> FoundSpotlights;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASpotlightActor::StaticClass(), FoundSpotlights);

	Spotlights.Reserve(FoundSpotlights.Num());
	for (AActor* Actor : FoundSpotlights)
	{
		if (ASpotlightActor* Spotlight = Cast<ASpotlightActor>(Actor))
		{
			Spotlight->RegisterPuzzleManager(this);
			Spotlights.Add(Spotlight);
		}
	}
}

int32 ADocksPuzzleManager::GetNextActivationOrder()
{
	return GlobalLightCounter++;
}

void ADocksPuzzleManager::StartPlayerTurn()
{
	if (bPuzzleComplete)
	{
		return;
	}

	CurrentTurn = EDocksPuzzleTurn::Player;
	BP_PlayerTurnStarted();
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
	if (bPuzzleComplete)
	{
		return;
	}

	CurrentTurn = EDocksPuzzleTurn::Gulls;
	BP_GullTurnStarted();

	ActiveGullsRemaining = 0;

	for (AGullActor* Gull : Gulls)
	{
		if (Gull && Gull->StartTurn(PuzzleLights, this, RestPoints))
		{
			ActiveGullsRemaining++;
		}
	}

	if (ActiveGullsRemaining == 0)
	{
		EndGullTurn();
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

void ADocksPuzzleManager::NotifyGullTurnStepComplete(AGullActor* /*Gull*/)
{
	if (CurrentTurn != EDocksPuzzleTurn::Gulls)
	{
		return;
	}

	ActiveGullsRemaining = FMath::Max(0, ActiveGullsRemaining - 1);

	if (ActiveGullsRemaining == 0)
	{
		EndGullTurn();
	}
}

void ADocksPuzzleManager::CheckWinCondition()
{
	for (AADockLightTemplate* Light : PuzzleLights)
	{
		if (!Light)
		{
			continue;
		}

		if (!Light->bRequiredForWin)
		{
			continue;
		}

		if (!Light->bIsLit)
		{
			return;
		}
	}

	bPuzzleComplete = true;
	CurrentTurn = EDocksPuzzleTurn::Complete;
	BP_PuzzleCompleted();
}

void ADocksPuzzleManager::ResetPuzzle()
{
	GlobalLightCounter = 0;
	ActiveGullsRemaining = 0;

	for (AADockLightTemplate* Light : PuzzleLights)
	{
		if (Light)
		{
			Light->ResetLightState();
		}
	}

	for (AGullActor* Gull : Gulls)
	{
		if (Gull)
		{
			Gull->ResetForPuzzle();
		}
	}

	for (ASpotlightActor* Spotlight : Spotlights)
	{
		if (Spotlight)
		{
			Spotlight->ResetForPuzzle();
		}
	}

	bPuzzleComplete = false;
	CurrentTurn = EDocksPuzzleTurn::Player;

	StartPlayerTurn();
}
