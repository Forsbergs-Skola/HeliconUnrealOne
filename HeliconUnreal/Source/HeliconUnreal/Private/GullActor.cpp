#include "GullActor.h"
#include "ADockLightTemplate.h"
#include "DocksPuzzleManager.h"
#include "AGullRestPoint.h"

AGullActor::AGullActor()
{
	PrimaryActorTick.bCanEverTick = true;
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

	if (AGullRestPoint* StartPoint = FindBlockingRestPoint(BestTarget->GetActorLocation(), RestPoints))
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
	const FVector LineDir = Destination - Start;
	const float LineLengthSq = LineDir.SizeSquared();

	AGullRestPoint* Best = nullptr;
	float BestDist = TNumericLimits<float>::Max();

	for (AGullRestPoint* RestPoint : RestPoints)
	{
		if (!RestPoint)
		{
			continue;
		}

		const FVector ToPoint = RestPoint->GetActorLocation() - Start;

		const float T = LineLengthSq > 0.f
			? FVector::DotProduct(ToPoint, LineDir) / LineLengthSq
			: 0.f;

		if (T <= 0.f || T >= 1.f)
		{
			continue;
		}

		const FVector ClosestPointOnLine = Start + LineDir * T;
		const float DistFromLine = FVector::Dist(RestPoint->GetActorLocation(), ClosestPointOnLine);

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

			const FVector TargetLocation = Target->GetActorLocation();
			const float Distance = FVector::Dist(GetActorLocation(), TargetLocation);

			if (Distance <= ArrivalDistance)
			{
				if (CurrentWaypoint)
				{
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
