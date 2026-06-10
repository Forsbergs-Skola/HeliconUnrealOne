// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseWeatherManipulator.generated.h"

UCLASS()
class HELICONUNREAL_API ABaseWeatherManipulator : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseWeatherManipulator();

	UFUNCTION(BlueprintImplementableEvent)
	void TestAddWeatherProgression();

protected:
	virtual void BeginPlay() override;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Test")
	int32 ProgressionAmount;
};
