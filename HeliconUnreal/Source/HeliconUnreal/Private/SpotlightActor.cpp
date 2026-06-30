#include "SpotlightActor.h"
#include "ADockLightTemplate.h"
#include "DocksPuzzleManager.h"
#include "DrawDebugHelpers.h"

ASpotlightActor::ASpotlightActor()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ASpotlightActor::RegisterPuzzleManager(ADocksPuzzleManager* InPuzzleManager)
{
	PuzzleManager = InPuzzleManager;
}

void ASpotlightActor::ResetForPuzzle()
{
	CurrentTarget = nullptr;
	ContactTime = 0.f;
}

void ASpotlightActor::Interact_Implementation()
{
	bIsControlled = true;
}

AADockLightTemplate* ASpotlightActor::FindUnlitLightAlongTrace(
	const FVector& Start,
	const FVector& End,
	bool& bOutHit) const
{
	bOutHit = false;

	TArray<FHitResult> Hits;
	FCollisionQueryParams Params(SCENE_QUERY_STAT(SpotlightTrace), false, this);

	if (!GetWorld()->LineTraceMultiByChannel(Hits, Start, End, TraceChannel, Params))
	{
		return nullptr;
	}

	bOutHit = true;

	for (const FHitResult& Hit : Hits)
	{
		AADockLightTemplate* Light = Cast<AADockLightTemplate>(Hit.GetActor());
		if (Light && !Light->bIsLit)
		{
			return Light;
		}
	}

	return nullptr;
}

void ASpotlightActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!bIsControlled)
	{
		return;
	}

	if (PuzzleManager && PuzzleManager->GetCurrentTurn() != EDocksPuzzleTurn::Player)
	{
		CurrentTarget = nullptr;
		ContactTime = 0.f;
		return;
	}

	const FVector Start = GetActorLocation();
	const FVector End = Start + (GetActorForwardVector() * TraceDistance);

	bool bHit = false;
	AADockLightTemplate* HitTarget = FindUnlitLightAlongTrace(Start, End, bHit);

	if (bDrawDebugTrace)
	{
		DrawDebugLine(GetWorld(), Start, End, bHit ? FColor::Red : FColor::Green, false, 0.1f);
	}

	if (HitTarget != CurrentTarget)
	{
		CurrentTarget = HitTarget;
		ContactTime = 0.f;
	}

	if (CurrentTarget)
	{
		ContactTime += DeltaTime;
	}
	else
	{
		ContactTime = 0.f;
	}

	if (CurrentTarget && ContactTime >= RequiredHoldTime)
	{
		CurrentTarget->LightOn();

		ContactTime = 0.f;
		CurrentTarget = nullptr;

		if (PuzzleManager)
		{
			PuzzleManager->EndPlayerTurn();
		}
	}
}