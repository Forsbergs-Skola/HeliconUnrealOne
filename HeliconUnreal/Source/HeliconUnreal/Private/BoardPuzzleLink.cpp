#include "BoardPuzzleLink.h"

ABoardPuzzleLink::ABoardPuzzleLink()
{
	PrimaryActorTick.bCanEverTick = false;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	LinkMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LinkMesh"));
	LinkMesh->SetupAttachment(RootComponent);
}

void ABoardPuzzleLink::BeginPlay()
{
	Super::BeginPlay();
	
	if (!NonLinkedMaterial)
	{
		UE_LOG(LogTemp, Warning, TEXT("No NonLinked Material!"));
	}
	LinkMesh->SetMaterial(0, NonLinkedMaterial);
	
	if (LinkID.IsEmpty())
	{
		UE_LOG(LogTemp, Warning, TEXT("No Link ID!"));
	}
}

void ABoardPuzzleLink::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABoardPuzzleLink::SetIsUnlocked(bool value)
{
	if (value == bIsUnlocked) { return; }
	bIsUnlocked = value;
	
	if (value)
	{
		ChangeMaterial(ELinkStatus::Linked);
		return;
	}
	
	if (!value)
	{
		ChangeMaterial(ELinkStatus::NotLinked);
	}
	
}

bool ABoardPuzzleLink::GetIsUnlocked() const
{
	return bIsUnlocked;
}

void ABoardPuzzleLink::ChangeMaterial(ELinkStatus LinkStatus)
{
	if (!LinkedMaterial)
	{
		UE_LOG(LogTemp, Warning, TEXT("No Linked Material!"));
	}
	
	switch (LinkStatus)
	{
		case ELinkStatus::NotLinked: LinkMesh->SetMaterial(0, NonLinkedMaterial); break;
		case ELinkStatus::Linked: LinkMesh->SetMaterial(0, LinkedMaterial); break;
	}	
}

FText& ABoardPuzzleLink::GetID()
{
	return LinkID;
}



