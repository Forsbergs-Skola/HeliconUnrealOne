// Fill out your copyright notice in the Description page of Project Settings.


#include "GullActor.h"

// Sets default values
AGullActor::AGullActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	State = EGullState::Idle;
	bHasLockedTarget = false;
}

// Called when the game starts or when spawned
void AGullActor::BeginPlay()
{
	Super::BeginPlay();
	
}

AADockLightTemplate* AGullActor::FindClosestLitLight(
	const TArray<AADockLightTemplate*>& Lights)
{
	AADockLightTemplate* BestLight = nullptr;
	float BestDistance = TNumericLimits<float>::Max();

	for (AADockLightTemplate* Light : Lights)
	{
		if (!Light)
		{
			continue;
		}

		if (!Light->bIsLit)
		{
			continue;
		}

		float Distance =
			FVector::Dist(
				GetActorLocation(),
				Light->GetActorLocation());

		if (Distance < BestDistance)
		{
			BestDistance = Distance;
			BestLight = Light;
		}

		UE_LOG(LogTemp, Warning, TEXT("Checking %s, bIsLit=%s"),
		*Light->GetName(),
		Light->bIsLit ? TEXT("TRUE") : TEXT("FALSE"));
	}
	

	return BestLight;
}

void AGullActor::StartTurn(
	const TArray<AADockLightTemplate*>& Lights)
{
	if (bHasLockedTarget)
	{
		return;
	}

	AADockLightTemplate* ClosestLight =
		FindClosestLitLight(Lights);

	if (ClosestLight)
	{
		SetTarget(ClosestLight);

		UE_LOG(LogTemp, Warning,
			TEXT("Gull locked target: %s"),
			*ClosestLight->GetName());
	}
}

// Called every frame
void AGullActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	switch (State)
	{
	case EGullState::Idle:
		break;

	case EGullState::MovingToTarget:
		{
			if (!LockedTarget) return;

			FVector Dir = (LockedTarget->GetActorLocation() - GetActorLocation()).GetSafeNormal();
			SetActorLocation(GetActorLocation() + Dir * MoveSpeed * DeltaTime);

			break;
		}

	case EGullState::Swarming:
		// later
		break;
	}

}

void AGullActor::SetTarget(AActor* NewTarget)
{
	if (bHasLockedTarget)
		return;

	LockedTarget = NewTarget;
	bHasLockedTarget = true;
	State = EGullState::MovingToTarget;
}

