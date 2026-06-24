// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BoardPuzzleLink.generated.h"

UENUM(BlueprintType)
enum class ELinkStatus : uint8
{
	Linked     UMETA(DisplayName = "Linked"),
	NotLinked  UMETA(DisplayName = "Not Linked")
};

UCLASS()
class HELICONUNREAL_API ABoardPuzzleLink : public AActor
{
	GENERATED_BODY()
	
public:	
	ABoardPuzzleLink();

	UFUNCTION(BlueprintCallable)
	void SetIsLinked(bool value);
	
	UFUNCTION(BlueprintCallable)
	bool GetIsLinked() const;
	
	UFUNCTION(BlueprintCallable)
	void ChangeMaterial(ELinkStatus LinkStatus);
	
protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Node")
	bool bIsLinked;
	
	UPROPERTY(EditAnywhere, Category = "Link|Visual")
	UMaterialInterface* LinkedMaterial;

	UPROPERTY(EditAnywhere, Category = "Link|Visual")
	UMaterialInterface* NonLinkedMaterial;
	
	UPROPERTY(EditAnywhere, Category = "Link|Visual")
	TObjectPtr<UStaticMeshComponent> LinkMesh;
};
