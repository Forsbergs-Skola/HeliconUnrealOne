#include "ADockLightTemplate.h"
#include "DocksPuzzleManager.h"

AADockLightTemplate::AADockLightTemplate()
{
	PrimaryActorTick.bCanEverTick = false;
	bIsLit = false;
}

void AADockLightTemplate::RegisterPuzzleManager(ADocksPuzzleManager* InPuzzleManager)
{
	PuzzleManager = InPuzzleManager;
}

void AADockLightTemplate::LightOn()
{
	bIsLit = true;

	if (PuzzleManager)
	{
		ActivationOrder = PuzzleManager->GetNextActivationOrder();
	}

	BP_LightStateChanged(true);
}

void AADockLightTemplate::LightOff()
{
	bIsLit = false;
	BP_LightStateChanged(false);
}

void AADockLightTemplate::ResetLightState()
{
	bIsLit = false;
	ActivationOrder = -1;
	BP_LightStateChanged(false);
}
