#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Suspector.generated.h"

struct FEventTagsStruct;
class UCPP_HeliconGameInstance;

UENUM(BlueprintType)
enum class ESuspectBehaviour : uint8
{
   MoveRandom,
   MoveToPoint, // Only works if bool DisableRandom is true
   RotateRandom,
};

UCLASS()
class HELICONUNREAL_API ASuspector : public AActor
{
   GENERATED_BODY()
  
public:
   ASuspector();
   
   UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Suspect")
   TObjectPtr<UStaticMesh> StaticMesh;
   
   UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Suspect")
   TObjectPtr<UStaticMeshComponent> StaticMeshComponent;
  
   // Disables randomness and requires you to select a value from ESuspectBehaviour for the actor to do anything
   UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Suspect")
   bool bDisableRandom;
   
   UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Suspect")
   bool bUsePhysics;
   
   UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Suspect")
   bool bDisableRandomRotation;
   
   // You only need to select an enum value here if you disabled randomness
   UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Suspect")
   ESuspectBehaviour NonRandomBehaviour;
  
   // The actor will move to target points in order of the array
   // If you want to only move an object to a point, tick DisableRandom = true
   UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Suspect")
   TArray<TObjectPtr<class ATargetPoint>> TargetPoints;
  
   UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Suspect")
   float MinRotationValue;
   
   UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Suspect")
   float MaxRotationValue;

   UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Suspect")
   float MaxRandomMoveValue;

protected:
   virtual void BeginPlay() override;
   
   virtual void OnConstruction(const FTransform& Transform) override;


public:
   virtual void Tick(float Deltaime) override;
  
   UFUNCTION(BlueprintCallable, Category = "Suspect")
   void ExecuteSuspectBehaviour(FEventTagsStruct TagsStruct);
  
private:
   UFUNCTION()
   void OnMoveRandom();
  
   UFUNCTION()
   void OnMoveToPoint(); 
  
   UFUNCTION()
   void OnRotateRandom();
   
   UFUNCTION()
   void BindEvents(const UCPP_HeliconGameInstance* GameInstance);
   
   UFUNCTION()
   void AddDebugMsg(const FString& Msg);
   
   UFUNCTION()
   ESuspectBehaviour RandomBehaviour();
  
   int CurrentTargetPointIndex = 0;
   int CurrentRotationIndex = 0;
   int MaxRandomCheckRotation = 20;
   
   FVector StartingLocation;
};
