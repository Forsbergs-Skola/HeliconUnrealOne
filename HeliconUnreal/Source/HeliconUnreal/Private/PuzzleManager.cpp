
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
