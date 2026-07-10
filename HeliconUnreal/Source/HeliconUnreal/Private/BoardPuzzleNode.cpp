#include "BoardPuzzleNode.h"
#include "Components/PrimitiveComponent.h"
#include "Components/BoxComponent.h"
#include "BoardPuzzleLink.h"
#include "BoardPuzzleBoard.h"
#include "DebugUtility.h"
#include "CPP_HeliconGameInstance.h"


ABoardPuzzleNode::ABoardPuzzleNode()
{
    PrimaryActorTick.bCanEverTick = false;

    RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

    ClickBox = CreateDefaultSubobject<UBoxComponent>(TEXT("ClickBox"));
    ClickBox->SetupAttachment(RootComponent);

    ClickBox->SetBoxExtent(FVector(20.f));

    ClickBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    ClickBox->SetCollisionResponseToAllChannels(ECR_Ignore);
    ClickBox->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);

    NodeMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("NodeMesh"));
    NodeMesh->SetupAttachment(ClickBox);

    NodeMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}


void ABoardPuzzleNode::BeginPlay()
{
    Super::BeginPlay();

    if (NodeMesh && NodeMaterial)
    {
        NodeMesh->SetMaterial(0, NodeMaterial);
    }

    ClickBox->OnClicked.AddDynamic(
        this,
        &ABoardPuzzleNode::OnNodeClicked
    );
}


void ABoardPuzzleNode::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}


void ABoardPuzzleNode::OnNodeClicked(UPrimitiveComponent* ClickedComp, FKey ButtonPressed)
{
    UnlockLink();
}


void ABoardPuzzleNode::UnlockLink()
{
    SCREEN_LOG(3, FColor::Yellow,
        TEXT("Unlocking node {0}"),
        *GetName());


    // Ending nodes don't own links.
    // They only validate completion.
    if (bIsEndingNode)
    {
        HandleEndingNode();
        return;
    }


    if (!OwnedLink)
    {
        SCREEN_LOG(3, FColor::Red,
            TEXT("{0} has no OwnedLink assigned"),
            *GetName());

        return;
    }


    if (OwnedLink->GetIsUnlocked())
    {
        SCREEN_LOG(3, FColor::Yellow,
            TEXT("Link already unlocked"));

        return;
    }


    HandleNormalNode();
}


bool ABoardPuzzleNode::CheckCompletion()
{
    if (!Board)
    {
        SCREEN_LOG(3, FColor::Red,
            TEXT("Board is NULL on {0}"),
            *GetName());

        return false;
    }


    if (Board->HasCompletedCorrectly())
    {
        if (NodeMesh && EndingNodeMaterial)
        {
            NodeMesh->SetMaterial(0, EndingNodeMaterial);
        }

        SCREEN_LOG(3, FColor::Green,
            TEXT("Board completed"));

        return true;
    }


    SCREEN_LOG(3, FColor::Yellow,
        TEXT("Board not completed"));

    return false;
}


void ABoardPuzzleNode::NotifyCompletion()
{
    UCPP_HeliconGameInstance* GameInstance =
        Cast<UCPP_HeliconGameInstance>(GetWorld()->GetGameInstance());


    if (!GameInstance || !Board)
    {
        return;
    }


    FEventTagsStruct TagStruct;

    TArray<FName> TagList;

    TagList.Add("BOARD_PUZZLE");
    TagList.Add(*Board->ID().ToString());

    TagStruct.TagsList = TagList;


    GameInstance->EventRelay->NotifyGameDataUpdated(TagStruct);
}


void ABoardPuzzleNode::UpdateBoard()
{
    if (!Board || !OwnedLink)
    {
        return;
    }


    Board->AddCompletedLinks(
        OwnedLink->GetID()
    );
}


void ABoardPuzzleNode::HandleEndingNode()
{
    if (!bIsEndingNode)
    {
        return;
    }


    if (CheckCompletion())
    {
        NotifyCompletion();
    }
}


void ABoardPuzzleNode::HandleNormalNode()
{
    if (!OwnedLink)
    {
        return;
    }


    if (!bIsStartingNode)
    {
        for (const ABoardPuzzleLink* Link : ConnectedLinks)
        {
            if (!Link)
            {
                continue;
            }


            if (!Link->GetIsUnlocked())
            {
                SCREEN_LOG(3, FColor::Yellow,
                    TEXT("Previous link is still locked"));

                return;
            }
        }
    }


    OwnedLink->SetIsUnlocked(true);

    UpdateBoard();


    if (NodeMesh && NodeMaterial)
    {
        NodeMesh->SetMaterial(0, NodeMaterial);
    }
}


void ABoardPuzzleNode::Reset()
{
    if (OwnedLink)
    {
        OwnedLink->SetIsUnlocked(false);


        if (Board)
        {
            Board->RemoveCompletedLink(
                OwnedLink->GetID()
            );
        }
    }


    if (NodeMesh && NodeMaterial)
    {
        NodeMesh->SetMaterial(0, NodeMaterial);
    }
}