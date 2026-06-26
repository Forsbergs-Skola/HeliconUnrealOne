// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ADockLightTemplate.h"
#include "GameFramework/Actor.h"
#include "GullActor.generated.h"

UENUM()
enum class EGullState : uint8
{
	Idle,
	MovingToTarget,
	Swarming
};

UCLASS()


class HELICONUNREAL_API AGullActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGullActor();

	UPROPERTY()
	AActor* LockedTarget;

	UPROPERTY()
	FVector NestLocation;

	UPROPERTY()
	bool bHasLockedTarget;

	UPROPERTY()
	float MoveSpeed = 300.f;

	UFUNCTION()
	void SetTarget(AActor* NewTarget);

	UPROPERTY(VisibleInstanceOnly)
	EGullState State;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	AADockLightTemplate* FindClosestLitLight(const TArray<AADockLightTemplate*>& Lights);

	UFUNCTION()
	void StartTurn(const TArray<AADockLightTemplate*>& Lights);

};
