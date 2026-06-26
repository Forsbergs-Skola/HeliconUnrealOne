// Fill out your copyright notice in the Description page of Project Settings.


#include "SpotlightActor.h"

// Sets default values
ASpotlightActor::ASpotlightActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASpotlightActor::BeginPlay()
{
	Super::BeginPlay();
	PuzzleManager = Cast<ADocksPuzzleManager>(
		UGameplayStatics::GetActorOfClass(
			GetWorld(),
			ADocksPuzzleManager::StaticClass()
		)
	);
}

void ASpotlightActor::Interact_Implementation()
{
	UE_LOG(LogTemp, Warning, TEXT("Spotlight Interacted"));

	bIsControlled = true;
}

void ASpotlightActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!bIsControlled)
	{
		return;
	}

	FVector Start = GetActorLocation();
	FVector End = Start + (GetActorForwardVector() * 2000.f);

	FHitResult Hit;

	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);

	bool bHit = GetWorld()->LineTraceSingleByChannel(
		Hit,
		Start,
		End,
		ECC_Visibility,
		Params
	);

	DrawDebugLine(GetWorld(), Start, End, bHit ? FColor::Red : FColor::Green, false, 0.1f);

	// -------------------------
	// GET ACTOR
	// -------------------------
	AActor* HitActor = Hit.GetActor();
	AADockLightTemplate* HitTarget = nullptr;

	if (HitActor)
	{

		HitTarget = Cast<AADockLightTemplate>(HitActor);

		if (HitTarget && HitTarget->bIsLit)
		{
			// already solved → ignore completely
			CurrentTarget = nullptr;
			ContactTime = 0.f;
			return;
		}

		if (HitTarget)
		{
			
		}
	}

	// -------------------------
	// TARGET SWITCH LOGIC
	// -------------------------
	if (HitTarget != CurrentTarget)
	{
		CurrentTarget = HitTarget;
		ContactTime = 0.f;
	}

	// -------------------------
	// HOLD LOGIC
	// -------------------------
	if (CurrentTarget)
	{
		ContactTime += DeltaTime;
	}
	else
	{
		ContactTime = 0.f;
	}

	

	// -------------------------
	// ACTIVATE
	// -------------------------
	if (CurrentTarget && !CurrentTarget->bIsLit && ContactTime >= RequiredHoldTime)
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




