// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DoorBase.generated.h"

UCLASS()
class HELICONUNREAL_API ADoorBase : public AActor
{
	GENERATED_BODY()
	
public:	
	ADoorBase();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "General")
	TObjectPtr<class UStaticMesh> DoorMeshAsset;

	TObjectPtr<class UStaticMeshComponent> DoorMeshComp;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "General")
	TObjectPtr<class UStaticMesh> FrameMeshAsset;

	TObjectPtr<class UStaticMeshComponent> FrameMeshComp;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "General")
	bool bUsePhysics;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

};
