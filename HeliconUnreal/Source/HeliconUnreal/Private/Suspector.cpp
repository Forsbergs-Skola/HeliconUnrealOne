#include "Suspector.h"
#include "CPP_HeliconGameInstance.h"
#include "Engine/Engine.h"
#include "Engine/TargetPoint.h"
#include "Math/UnrealMathUtility.h"

ASuspector::ASuspector()
{
   RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
   
   PrimaryActorTick.bCanEverTick = true;
   StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh Component")); 
   StaticMeshComponent->SetupAttachment(RootComponent);
}


void ASuspector::BeginPlay()
{
   Super::BeginPlay();
  
   const UCPP_HeliconGameInstance* GameInstance = Cast<UCPP_HeliconGameInstance>(GetWorld()->GetGameInstance());
  
   BindEvents(GameInstance);
   
   
}

void ASuspector::OnConstruction(const FTransform& Transform)
{
   Super::OnConstruction(Transform);
   
   if (StaticMesh)
   {
      StaticMeshComponent->SetStaticMesh(StaticMesh);
   }
}


void ASuspector::Tick(float DeltaTime)
{
   Super::Tick(DeltaTime);
}

void ASuspector::ExecuteSuspectBehaviour(FEventTagsStruct TagsStruct)
{
   ESuspectBehaviour Behaviour = RandomBehaviour();
   switch (Behaviour)
   {
   case ESuspectBehaviour::MoveRandom:
      OnMoveRandom();
      AddDebugMsg("Suspector Executing Move Random");
      break;
   case ESuspectBehaviour::RotateRandom:
      OnRotateRandom();
      AddDebugMsg("Suspector Executing Rotate Random");
      break;
   case ESuspectBehaviour::MoveToPoint:
      OnMoveToPoint();
      AddDebugMsg("Suspector Executing Move ToPoint");
      break;
   default:
      OnMoveRandom();
      AddDebugMsg("Defaulted to Move Random");
   }
}

void ASuspector::OnMoveToPoint() {
   if (!TargetPoints.IsValidIndex(CurrentTargetPointIndex))
   {
      CurrentTargetPointIndex = 0;
   }
  
   const ATargetPoint* Target = TargetPoints[CurrentTargetPointIndex];
   if (!Target)
   {
      UE_LOG(LogTemp, Error, TEXT("Target point element is nullptr"));
      return;
   }
  
   SetActorLocation(Target->GetActorLocation(), false);
   CurrentTargetPointIndex = (CurrentTargetPointIndex + 1) % TargetPoints.Num();
}

void ASuspector::OnMoveRandom() {
   const FVector NewLocation(
      GetActorLocation().X + FMath::RandRange(0.0f,  MaxRandomMoveValue),
      GetActorLocation().Y + FMath::RandRange(0.0f,  MaxRandomMoveValue),
      GetActorLocation().Z 
   );
   
   SetActorLocation(NewLocation, false);
}

void ASuspector::OnRotateRandom() {
   
   const FRotator NewRotation(
      FMath::RandRange(MinRotationValue, MaxRotationValue),
      FMath::RandRange(MinRotationValue, MaxRotationValue),
      FMath::RandRange(MinRotationValue, MaxRotationValue)
   );
   
   SetActorRotation(NewRotation);
}

void ASuspector::BindEvents(const UCPP_HeliconGameInstance* GameInstance)
{
   if (GameInstance)
   {
      GameInstance->EventRelay->OnPuzzleCompleted.AddDynamic(this, &ASuspector::ExecuteSuspectBehaviour);
   }
}

ESuspectBehaviour ASuspector::RandomBehaviour()
{
   if (bDisableRandom)
   {
      return ESuspectBehaviour::MoveToPoint;
   }
   
   const int Result = FMath::RandRange(0, 50);   
   
   
   if (Result <= 50 && Result > 0) return ESuspectBehaviour::MoveRandom;
   if (Result <= 100 && Result > 50) return ESuspectBehaviour::RotateRandom;
   return ESuspectBehaviour::MoveRandom;
}

// Refactor 
// Change to UE_LOG when system is stable 
void ASuspector::AddDebugMsg(const FString& Msg)
{
   if (GEngine)
   {
      GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, Msg);
   }
}