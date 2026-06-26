// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ADockLightTemplate.generated.h"

UCLASS()
class HELICONUNREAL_API AADockLightTemplate : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AADockLightTemplate();

	UPROPERTY()
	class ADocksPuzzleManager* PuzzleManager;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Light")
	bool bIsLit;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Light")
	float GullPriority;

	UFUNCTION(BlueprintCallable)
	virtual void LightOn();

	UFUNCTION(BlueprintCallable)
	virtual void LightOff();

	UPROPERTY(BlueprintReadOnly, Category="Light")
	bool bIsLocked = false;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	bool bPendingActivation;
	float ActivationTimer;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
