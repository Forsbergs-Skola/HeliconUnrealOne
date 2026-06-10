#include "DoorBase.h"

#include "Engine/StaticMesh.h"
#include "Components/StaticMeshComponent.h"

ADoorBase::ADoorBase()
{
	PrimaryActorTick.bCanEverTick = true;

	DoorMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door Mesh"));
	DoorMeshComp->SetupAttachment(RootComponent);

	FrameMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Frame Mesh"));
	FrameMeshComp->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ADoorBase::BeginPlay()
{
	Super::BeginPlay();
	DoorMeshComp->SetStaticMesh(DoorMeshAsset);
	FrameMeshComp->SetStaticMesh(FrameMeshAsset);
}

// Called every frame
void ADoorBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

