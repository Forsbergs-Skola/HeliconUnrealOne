#include "BoardPuzzleNode.h"
#include "Components/PrimitiveComponent.h"
#include "BoardPuzzleLink.h"
#include "BoardPuzzleBoard.h"
#include "DebugUtility.h"
#include "CPP_HeliconGameInstance.h"
#include "Components/SphereComponent.h"

ABoardPuzzleNode::ABoardPuzzleNode()
{
    PrimaryActorTick.bCanEverTick = false;

    RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

    ClickSphere = CreateDefaultSubobject<USphereComponent>(TEXT("ClickSphere"));
    ClickSphere->SetupAttachment(RootComponent);

    ClickSphere->InitSphereRadius(20.f); 

    ClickSphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    ClickSphere->SetCollisionResponseToAllChannels(ECR_Ignore);
    ClickSphere->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);

    NodeMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("NodeMesh"));
    NodeMesh->SetupAttachment(ClickSphere);
    
    ClickSphere->SetGenerateOverlapEvents(false);
    ClickSphere->bSelectable = true; 
}

void ABoardPuzzleNode::BeginPlay()
{
    Super::BeginPlay();

    if (bIsEndingNode && !EndingNodeMaterial)
    {
        SCREEN_LOG(3, FColor::Red, TEXT("No EndingNodeMaterial assigned to %s!"), *GetName());
    }

    if (!NodeMaterial)
    {
        SCREEN_LOG(3, FColor::Red, TEXT("No NodeMaterial assigned to %s!"), *GetName());
    }
    
    if (NodeMesh && NodeMaterial)
    {
        NodeMesh->SetMaterial(0, NodeMaterial);
    }

    ClickSphere->OnClicked.AddDynamic(this, &ABoardPuzzleNode::OnNodeClicked);
}

void ABoardPuzzleNode::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void ABoardPuzzleNode::OnNodeClicked(UPrimitiveComponent* ClickedComp, FKey ButtonPressed)
{
    UE_LOG(LogTemp, Warning, TEXT("Node clicked!"));
    UnlockLink();
}

void ABoardPuzzleNode::UnlockLink()
{ 
    SCREEN_LOG(3, FColor::Yellow, TEXT("=== UnlockLink() started on Node: %s ==="), *GetName());

    SCREEN_LOG(3, FColor::Yellow, TEXT("StartingNode: %s | EndingNode: %s"), bIsStartingNode ? TEXT("TRUE") : TEXT("FALSE"),
        bIsEndingNode ? TEXT("TRUE") : TEXT("FALSE"));
    
    if (OwnedLink)
    {
        if (OwnedLink->GetIsUnlocked())
        {
            SCREEN_LOG(3, FColor::Yellow, TEXT("STOPPED: Link %s is already unlocked. Skipping duplicate registration."), *OwnedLink->GetName());
            HandleEndingNode(); 
            return;
        }

        HandleNormalNode();
    }
    else 
    {
        SCREEN_LOG(3, FColor::Yellow, TEXT("%s has no OwnedLink, skipping link unlock logic."), *GetName());
    }

    HandleEndingNode();
}

bool ABoardPuzzleNode::CheckCompletion()
{
    SCREEN_LOG(3, FColor::Yellow, TEXT("HasCompletedCorrectly = %s"), 
           Board->HasCompletedCorrectly() ? TEXT("TRUE") : TEXT("FALSE"));
    
    if (Board->HasCompletedCorrectly())
    {
        if (NodeMesh && EndingNodeMaterial)
        {
            NodeMesh->SetMaterial(0, EndingNodeMaterial);
                
            SCREEN_LOG(3, FColor::Yellow, TEXT("Applied ending material to %s"), *GetName());
        }
        else
        {
            SCREEN_LOG(3, FColor::Red, TEXT("NodeMesh or EndingNodeMaterial is NULL!"));
        }

        SCREEN_LOG(3, FColor::Green, TEXT("Board( %s ) Completed!"), Board->ID());
        return true;
    }
    SCREEN_LOG(3, FColor::Red, TEXT("Board( %s ) Not Completed!"), Board->ID());
    return false;
}

void ABoardPuzzleNode::NotifyCompletion()
{
    UCPP_HeliconGameInstance* GameInstance = Cast<UCPP_HeliconGameInstance>(GetWorld()->GetGameInstance());
	
    if (GameInstance)
    {
        FEventTagsStruct TagStruct;
        TArray<FName> TagList;
        TagList.Add("BOARD_PUZZLE");
        TagList.Add(*Board->ID().ToString());
        TagStruct.TagsList = TagList;
        GameInstance->EventRelay->NotifyGameDataUpdated(TagStruct);
        return;
    }
    SCREEN_LOG(3, FColor::Red, TEXT("Failed to get or cast to game instance!"));
}

void ABoardPuzzleNode::UpdateBoard()
{
    if (Board)
    {
        Board->AddCompletedLinks(OwnedLink->GetID());
    }
    else
    {
        SCREEN_LOG(3, FColor::Red, TEXT("Board ( %s ) pointer is NULL on %s!"), Board->ID() ,*GetName());
    }
}

void ABoardPuzzleNode::HandleEndingNode()
{
    if (bIsEndingNode)
    {
        if (!Board)
        {
            SCREEN_LOG(3, FColor::Red, TEXT("STOPPED: Board is NULL on %s!"), *GetName());
            return;
        }

        if (CheckCompletion())
        {
            NotifyCompletion();
        }
    }
}

void ABoardPuzzleNode::HandleNormalNode()
{
    if (!bIsStartingNode)
    {
        if (ConnectedLinks.IsEmpty())
        {
            SCREEN_LOG(3, FColor::Red, TEXT("STOPPED: %s has no connected links!"), *GetName());
            return; 
        }

        bool bAllLinksUnlocked = true;

        for (const ABoardPuzzleLink* Link : ConnectedLinks)
        {
            if (!Link)
            {
                continue;
            }
            
            SCREEN_LOG(3, FColor::Cyan, TEXT("Checking Link %s. Status: %s"), *Link->GetName(),
                Link->GetIsUnlocked() ? TEXT("Unlocked") : TEXT("LOCKED"));
            
            if (!Link->GetIsUnlocked())
            {
                bAllLinksUnlocked = false;
                break;
            }
        }

        if (!bAllLinksUnlocked)
        {
            SCREEN_LOG(3, FColor::Yellow, TEXT("STOPPED: Previous links are still locked."));
            return; // Hard stop! Prevents moving down to the unlock logic below
        }
    }

    if (OwnedLink)
    {
        OwnedLink->SetIsUnlocked(true);
        UpdateBoard();
    }
}

void ABoardPuzzleNode::Reset()
{
    if (OwnedLink)
    {
        OwnedLink->SetIsUnlocked(false);
        
        if (Board)
        {
            Board->RemoveCompletedLink(OwnedLink->GetID());
        }
        else
        {
            SCREEN_LOG(3, FColor::Red, TEXT("%s: Board pointer is NULL!"), *GetName());
        }
    }
    else
    {
        SCREEN_LOG(3, FColor::Red, TEXT("%s was clicked, but its OwnedLink is NULL!"), *GetName());
    }
}