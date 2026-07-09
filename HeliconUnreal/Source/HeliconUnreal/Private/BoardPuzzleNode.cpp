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
}

void ABoardPuzzleNode::BeginPlay()
{
    Super::BeginPlay();

    if (bIsEndingNode && !EndingNodeMaterial)
    {
        SCREEN_LOG(3, FColor::Red, TEXT("No EndingNodeMaterial assigned to {0}!"), *GetName());
    }

    if (!NodeMaterial)
    {
        SCREEN_LOG(3, FColor::Red, TEXT("No NodeMaterial assigned to {0}!"), *GetName());
    }

    if (NodeMesh && NodeMaterial)
    {
        NodeMesh->SetMaterial(0, NodeMaterial);
    }

    ClickBox->OnClicked.AddDynamic(this, &ABoardPuzzleNode::OnNodeClicked);
}

void ABoardPuzzleNode::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void ABoardPuzzleNode::OnNodeClicked(UPrimitiveComponent* ClickedComp, FKey ButtonPressed)
{
    APlayerController* PC = GetWorld()->GetFirstPlayerController();

    if (!PC)
    {
        return;
    }

    FVector MouseLocation;
    FVector MouseDirection;

    if (!PC->DeprojectMousePositionToWorld(MouseLocation, MouseDirection))
    {
        return;
    }

    FVector TraceEnd = MouseLocation + MouseDirection * 10000.f;

    FHitResult Hit;

    FCollisionQueryParams Params;
    Params.AddIgnoredActor(PC->GetPawn());

    if (GetWorld()->LineTraceSingleByChannel(
        Hit,
        MouseLocation,
        TraceEnd,
        ECC_Visibility,
        Params))
    {
        ABoardPuzzleNode* HitNode = Cast<ABoardPuzzleNode>(Hit.GetActor());

        if (HitNode)
        {
            SCREEN_LOG(3, FColor::Green,
                TEXT("Clicked Node: {0}"),
                *HitNode->GetName());

            HitNode->UnlockLink();
        }
    }
}

void ABoardPuzzleNode::UnlockLink()
{
    SCREEN_LOG(3, FColor::Yellow,
        TEXT("=== UnlockLink() started on Node: {0} ==="),
        *GetName());

    if (OwnedLink)
    {
        if (OwnedLink->GetIsUnlocked())
        {
            HandleEndingNode();
            return;
        }

        HandleNormalNode();
    }

    HandleEndingNode();
}

bool ABoardPuzzleNode::CheckCompletion()
{
    if (!Board)
    {
        return false;
    }

    if (Board->HasCompletedCorrectly())
    {
        if (NodeMesh && EndingNodeMaterial)
        {
            NodeMesh->SetMaterial(0, EndingNodeMaterial);
        }

        return true;
    }

    return false;
}

void ABoardPuzzleNode::NotifyCompletion()
{
    UCPP_HeliconGameInstance* GameInstance =
        Cast<UCPP_HeliconGameInstance>(GetWorld()->GetGameInstance());

    if (GameInstance && Board)
    {
        FEventTagsStruct TagStruct;

        TArray<FName> TagList;
        TagList.Add("BOARD_PUZZLE");
        TagList.Add(*Board->ID().ToString());

        TagStruct.TagsList = TagList;

        GameInstance->EventRelay->NotifyGameDataUpdated(TagStruct);
    }
}

void ABoardPuzzleNode::UpdateBoard()
{
    if (Board && OwnedLink)
    {
        Board->AddCompletedLinks(OwnedLink->GetID());
    }
}

void ABoardPuzzleNode::HandleEndingNode()
{
    if (bIsEndingNode && Board)
    {
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
        for (const ABoardPuzzleLink* Link : ConnectedLinks)
        {
            if (Link && !Link->GetIsUnlocked())
            {
                return;
            }
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
    }
}