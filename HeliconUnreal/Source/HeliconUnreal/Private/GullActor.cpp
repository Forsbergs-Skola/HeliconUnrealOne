#include "GullActor.h"
#include "ADockLightTemplate.h"
#include "DocksPuzzleManager.h"
#include "AGullRestPoint.h"

AGullActor::AGullActor()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AGullActor::BeginPlay()
{
	Super::BeginPlay();

	StartLocation = GetActorLocation();
	StartRotation = GetActorRotation();
}

FVector AGullActor::GetFlightLocation(const FVector& WorldLocation) const
{
	return WorldLocation + FVector(0.f, 0.f, FlightHeightOffset);
}

FVector AGullActor::GetFlightLocationForActor(const AActor* Target) const
{
	return Target ? GetFlightLocation(Target->GetActorLocation()) : FVector::ZeroVector;
}

bool AGullActor::HasReachedWaypoint(const AActor* Waypoint) const
{
	if (!Waypoint)
	{
		return false;
	}

	return FVector::Dist2D(GetActorLocation(), Waypoint->GetActorLocation()) <= ArrivalDistance;
}

bool AGullActor::HasReachedFlightTarget(const FVector& TargetLocation) const
{
	return FVector::Dist(GetActorLocation(), TargetLocation) <= ArrivalDistance;
}

AADockLightTemplate* AGullActor::FindBestTarget(const TArray<AADockLightTemplate*>& Lights) const
{
	AADockLightTemplate* BestDecoy = nullptr;
	int32 BestDecoyOrder = MAX_int32;

	for (AADockLightTemplate* Light : Lights)
	{
		if (!Light || !Light->bIsLit || !Light->bIsDecoy)
		{
			continue;
		}

		if (BestDecoy == nullptr || Light->ActivationOrder < BestDecoyOrder)
		{
			BestDecoy = Light;
			BestDecoyOrder = Light->ActivationOrder;
		}
	}

	if (BestDecoy)
	{
		return BestDecoy;
	}

	AADockLightTemplate* BestNormal = nullptr;
	int32 BestNormalOrder = MAX_int32;

	for (AADockLightTemplate* Light : Lights)
	{
		if (!Light || !Light->bIsLit || Light->bIsDecoy)
		{
			continue;
		}

		if (BestNormal == nullptr || Light->ActivationOrder < BestNormalOrder)
		{
			BestNormal = Light;
			BestNormalOrder = Light->ActivationOrder;
		}
	}

	return BestNormal;
}

bool AGullActor::StartTurn(
	const TArray<AADockLightTemplate*>& Lights,
	ADocksPuzzleManager* InPuzzleManager,
	const TArray<AGullRestPoint*>& RestPoints)
{
	PuzzleManager = InPuzzleManager;

	AADockLightTemplate* BestTarget = FindBestTarget(Lights);
	if (!BestTarget)
	{
		return false;
	}

	const bool bResumingFromRest = (State == EGullState::WaitingAtRestPoint);

	if (bResumingFromRest)
	{
		NextTarget = BestTarget;
		SetTarget(NextTarget);
		return true;
	}

	LockedTarget = nullptr;
	CurrentWaypoint = nullptr;
	NextTarget = nullptr;
	SwarmTimer = 0.f;
	State = EGullState::Idle;

	NextTarget = BestTarget;

	if (AGullRestPoint* StartPoint = FindBlockingRestPoint(
		GetFlightLocationForActor(BestTarget), RestPoints))
	{
		SetWaypoint(StartPoint);
	}
	else
	{
		SetTarget(BestTarget);
	}

	return true;
}

void AGullActor::ResetForPuzzle()
{
	LockedTarget = nullptr;
	NextTarget = nullptr;
	CurrentWaypoint = nullptr;
	PuzzleManager = nullptr;
	SwarmTimer = 0.f;
	State = EGullState::Idle;

	SetActorLocation(StartLocation);
	SetActorRotation(StartRotation);
}

void AGullActor::SetWaypoint(AActor* NewWaypoint)
{
	CurrentWaypoint = NewWaypoint;
	State = EGullState::MovingToTarget;
}

AGullRestPoint* AGullActor::FindBlockingRestPoint(
	const FVector& Destination,
	const TArray<AGullRestPoint*>& RestPoints) const
{
	const FVector Start = GetActorLocation();
	const FVector Start2D(Start.X, Start.Y, 0.f);
	const FVector Dest2D(Destination.X, Destination.Y, 0.f);
	const FVector LineDir = Dest2D - Start2D;
	const float LineLengthSq = LineDir.SizeSquared();

	AGullRestPoint* Best = nullptr;
	float BestDist = TNumericLimits<float>::Max();

	for (AGullRestPoint* RestPoint : RestPoints)
	{
		if (!RestPoint)
		{
			continue;
		}

		const FVector RestLocation = RestPoint->GetActorLocation();
		const FVector Rest2D(RestLocation.X, RestLocation.Y, 0.f);
		const FVector ToPoint = Rest2D - Start2D;

		const float T = LineLengthSq > 0.f
			? FVector::DotProduct(ToPoint, LineDir) / LineLengthSq
			: 0.f;

		if (T <= 0.f || T >= 1.f)
		{
			continue;
		}

		const FVector ClosestPointOnLine = Start2D + LineDir * T;
		const float DistFromLine = FVector::Dist2D(Rest2D, ClosestPointOnLine);

		if (DistFromLine <= RestPoint->GetBlockingRadius() && DistFromLine < BestDist)
		{
			BestDist = DistFromLine;
			Best = RestPoint;
		}
	}

	return Best;
}

void AGullActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	switch (State)
	{
	case EGullState::Idle:
	case EGullState::WaitingAtRestPoint:
		break;

	case EGullState::MovingToTarget:
		{
			AActor* Target = CurrentWaypoint ? CurrentWaypoint.Get() : LockedTarget.Get();

			if (!Target)
			{
				FinishTurn();
				return;
			}

			const FVector TargetLocation = GetFlightLocationForActor(Target);
			const bool bReachedWaypoint = CurrentWaypoint && HasReachedWaypoint(Target);
			const bool bReachedLight = !CurrentWaypoint && HasReachedFlightTarget(TargetLocation);

			if (bReachedWaypoint || bReachedLight)
			{
				if (CurrentWaypoint)
				{
					SetActorLocation(GetFlightLocation(Target->GetActorLocation()));

					CurrentWaypoint = nullptr;
					State = EGullState::WaitingAtRestPoint;

					if (PuzzleManager)
					{
						PuzzleManager->NotifyGullTurnStepComplete(this);
					}

					return;
				}

				EnterSwarming();
				return;
			}

			const FVector NewLocation = FMath::VInterpConstantTo(
				GetActorLocation(),
				TargetLocation,
				DeltaTime,
				MoveSpeed);

			SetActorLocation(NewLocation);
			break;
		}

	case EGullState::Swarming:
		SwarmTimer += DeltaTime;

		if (SwarmTimer >= SwarmDuration)
		{
			FinishTurn();
		}
		break;
	}
}

void AGullActor::SetTarget(AActor* NewTarget)
{
	LockedTarget = NewTarget;
	CurrentWaypoint = nullptr;
	State = EGullState::MovingToTarget;
}

void AGullActor::EnterSwarming()
{
	State = EGullState::Swarming;
	SwarmTimer = 0.f;
}

void AGullActor::FinishTurn()
{
	if (AADockLightTemplate* LightTarget = Cast<AADockLightTemplate>(LockedTarget))
	{
		LightTarget->LightOff();
	}

	LockedTarget = nullptr;
	NextTarget = nullptr;
	CurrentWaypoint = nullptr;
	SwarmTimer = 0.f;
	State = EGullState::Idle;

	if (PuzzleManager)
	{
		PuzzleManager->NotifyGullTurnStepComplete(this);
	}
}
