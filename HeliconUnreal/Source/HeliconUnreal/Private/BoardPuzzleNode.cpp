#include "BoardPuzzleNode.h"
#include "Components/PrimitiveComponent.h"
#include "TimerManager.h"
#include "BoardPuzzleLink.h"

ABoardPuzzleNode::ABoardPuzzleNode()
{
	PrimaryActorTick.bCanEverTick = false; 
	
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	NodeMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("NodeMesh"));
	
	NodeMesh->SetupAttachment(RootComponent);
}

void ABoardPuzzleNode::BeginPlay()
{
	Super::BeginPlay();
	if (NodeMaterial)
	{
		NodeMesh->SetMaterial(0, NodeMaterial);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Node does not have a Material!"));
	}
    
	if (UPrimitiveComponent* PrimComp = Cast<UPrimitiveComponent>(GetRootComponent()))
	{
		PrimComp->OnBeginCursorOver.AddDynamic(this, &ABoardPuzzleNode::OnNodeHoverBegin);
		PrimComp->OnEndCursorOver.AddDynamic(this, &ABoardPuzzleNode::OnNodeHoverEnd);
	}
}

void ABoardPuzzleNode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABoardPuzzleNode::OnNodeHoverBegin(UPrimitiveComponent* TouchedComponent)
{
	UE_LOG(LogTemp, Warning, TEXT("Cursor Entered Actor Starting countdown!..."));

	GetWorldTimerManager().SetTimer(
		HoverTimerHandle, 
		this, 
		&ABoardPuzzleNode::OnHoverTimerComplete, 
		RequiredHoverTime, 
		false
	);
}

void ABoardPuzzleNode::OnNodeHoverEnd(UPrimitiveComponent* TouchedComponent)
{
	UE_LOG(LogTemp, Warning, TEXT("Cursor Left Actor resetting countdown!"));
	GetWorldTimerManager().ClearTimer(HoverTimerHandle);
}

void ABoardPuzzleNode::OnHoverTimerComplete() const
{
	// All nodes should have an owned link
	if (!OwnedLink)
	{
		UE_LOG(LogTemp, Error, TEXT("Node does not own a Link!"));
		return;
	}
	
	// If the node is not a starting node it should have a connected link
	// If the connected link is not already linked you should not procced
	if (!bIsStartingNode)
	{
		if (!ConnectedLink)
		{
			UE_LOG(LogTemp, Error, TEXT("Non starting node does not have a connected link!"));
			return;
		}
		
		if (ConnectedLink->GetIsLinked())
		{
			OwnedLink->SetIsLinked((true));
			UE_LOG(LogTemp, Display, TEXT("linked the Owned link!"));
			return;
		}
		OwnedLink->SetIsLinked((false)); // Might not be needed since it is false by default 
		return;
	}
	
	OwnedLink->SetIsLinked((true));
	UE_LOG(LogTemp, Display, TEXT("linked the Owned link!"));
}