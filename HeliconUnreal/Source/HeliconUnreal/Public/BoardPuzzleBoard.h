// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BoardPuzzleBoard.generated.h"

UCLASS()
class HELICONUNREAL_API ABoardPuzzleBoard : public AActor
{
	GENERATED_BODY()
	
public:	
	ABoardPuzzleBoard();
	
	UFUNCTION(BlueprintCallable)
	TArray<FName>& GetCorrectLinkCompletionOrder();
	
	UFUNCTION(BlueprintCallable)
	TArray<FName>& GetCompletedNodes();
	
	UFUNCTION(BlueprintCallable)
	void AddCompletedLinks(const FName ID);
	
	UFUNCTION(BlueprintCallable)
	void RemoveCompletedLink(const FName ID);
	
	UFUNCTION(BlueprintCallable)
	bool HasCompletedCorrectly();
	
	UFUNCTION(BlueprintCallable)
	FName& ID() { return BoardID; }
	
protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Board)
	TObjectPtr<UStaticMeshComponent> BoardMesh;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Board)
	FName BoardID;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Board)
	UMaterialInterface* BoardMaterial;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Board)
	TArray<FName> CorrectLinkCompletionOrder;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Board)
	TArray<FName> CompletedLinks;
};
