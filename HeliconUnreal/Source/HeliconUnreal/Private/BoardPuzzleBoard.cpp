#include "BoardPuzzleBoard.h"

ABoardPuzzleBoard::ABoardPuzzleBoard()
{
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<UStaticMeshComponent>("RootComponent");
	BoardMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BoardMesh"));
	BoardMesh->SetupAttachment(RootComponent);
}

TArray<FText>& ABoardPuzzleBoard::GetCorrectLinkCompletionOrder()
{
	return CorrectLinkCompletionOrder;
}

TArray<FText>& ABoardPuzzleBoard::GetCompletedNodes()
{
	return CompletedLinks;
}

void ABoardPuzzleBoard::AddCompletedLinks(const FText ID)
{
	CompletedLinks.Add(ID);
}

bool ABoardPuzzleBoard::HasCompletedCorrectly()
{
	if (CompletedLinks.Num() != CorrectLinkCompletionOrder.Num())
	{
		return false;
	}

	for (int32 i = 0; i < CompletedLinks.Num(); i++)
	{
		if (!CompletedLinks[i].ToString().Equals(CorrectLinkCompletionOrder[i].ToString()))
		{
			return false;
		}
	}
	return true;
}

void ABoardPuzzleBoard::BeginPlay()
{
	Super::BeginPlay();
	
	if (BoardMaterial)
	{
		BoardMesh->SetMaterial(0, BoardMaterial);
	}
	
	if (CorrectLinkCompletionOrder.IsEmpty())
	{
		UE_LOG(LogTemp, Error, TEXT("No correct link completion order found"));
	}
}

void ABoardPuzzleBoard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

