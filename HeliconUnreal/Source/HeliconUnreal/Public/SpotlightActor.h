// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ADockLightTemplate.h"
#include "Interactable.h"
#include "DocksPuzzleManager.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "SpotlightActor.generated.h"


UCLASS()
class HELICONUNREAL_API ASpotlightActor : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpotlightActor();

	UPROPERTY()
	AADockLightTemplate* CurrentTarget;

	UPROPERTY()
	float ContactTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float RequiredHoldTime = 3.0f;

	UPROPERTY()
	ADocksPuzzleManager* PuzzleManager;

	UPROPERTY(BlueprintReadWrite)
	bool bIsControlled = false;

	virtual void Interact_Implementation() override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
