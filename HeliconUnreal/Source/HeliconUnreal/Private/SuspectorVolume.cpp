#include "SuspectorVolume.h"

#include "Math/UnrealMathUtility.h"

ASuspectorVolume::ASuspectorVolume()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ASuspectorVolume::OnConstruction(const FTransform& Transform){
	Super::OnConstruction(Transform);
	
}

// Called when the game starts or when spawned
void ASuspectorVolume::BeginPlay()
{
	Super::BeginPlay();
	VolumeScale = GetActorScale();
	
}

// Called every frame
void ASuspectorVolume::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASuspectorVolume::SpawnSuspectorActors()
{
	
	
}



