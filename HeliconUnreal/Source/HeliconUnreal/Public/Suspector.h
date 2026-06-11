#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Suspector.generated.h"

struct FEventTagsStruct;

UENUM(BlueprintType)
enum class ESuspectBehaviour : uint8
{
	MoveRandom,
	MoveToPoint, // Only works if bool DisableRandom is true
	RotateRandom,
	Rotate // Rotate using the FVector UPROPERTY
};

UCLASS()
class HELICONUNREAL_API ASuspector : public AActor
{
	GENERATED_BODY()
	
public:	
	ASuspector();
	
	// Disables randomness and requires you to select a value from ESuspectBehaviour for the actor to do anything
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Suspect")
	bool bDisableRandom;
	
	// You only need to select an enum value here if you disabled randomness 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Suspect")
	ESuspectBehaviour NonRandomBehaviour;
	
	// The actor will move to target points in order of the array 
	// If you want to only move an object to a point, tick DisableRandom = true 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Suspect")
	TArray<TObjectPtr<class ATargetPoint>> TargetPoints;
	
	// Use If random is disabled, and you want to rotate the actor. 
	// The vector value used to rotate is picked in order of the array
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Suspect")
	TArray<FVector> NonRandomRotations;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float Deltaime) override;
	
	void OnMoveRandom() const; 
	void OnMoveToPoint() const;
	
	void OnRotateRandom() const;
	void OnRotateToPoint() const;
	
	UFUNCTION(BlueprintCallable, Category = "Suspect")
	void ExecuteSuspectBehaviour(FEventTagsStruct TagsStruct);
};