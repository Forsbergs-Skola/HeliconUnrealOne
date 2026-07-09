
#include "PuzzleManager.h"

APuzzleManager::APuzzleManager()
{
	bStateB = false;
}

void APuzzleManager::ToggleRoomState()
{
	bStateB = !bStateB;
	
	GEngine->AddOnScreenDebugMessage(
	   -1,
	   2.f,
	   FColor::Green,
	   bStateB ? TEXT("STATE B") : TEXT("STATE A")
   );
	
	OnRoomStateChanged.Broadcast(bStateB);
}

void APuzzleManager::RegisterActivatedObject()
{
	ActivatedObjects++;
	
	GEngine->AddOnScreenDebugMessage(
	-1,
	2.f,
	FColor::Yellow,
	FString::Printf(TEXT("%d / %d"),
	ActivatedObjects,
	RequiredObjects)
);

	if (ActivatedObjects >= RequiredObjects)
	{
		GEngine->AddOnScreenDebugMessage(
			-1,
			2.f,
			FColor::Green,
			TEXT("Puzzle Unlocked!")
		);

		OnPuzzleUnlocked.Broadcast();
	}
}
