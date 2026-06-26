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
	TArray<FText>& GetCorrectLinkCompletionOrder();
	
	UFUNCTION(BlueprintCallable)
	TArray<FText>& GetCompletedNodes();
	
	UFUNCTION(BlueprintCallable)
	void AddCompletedLinks(const FText ID);
	
	UFUNCTION(BlueprintCallable)
	bool HasCompletedCorrectly();
	
	UFUNCTION(BlueprintCallable)
	FText& ID() { return BoardID; }
	
protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Board)
	TObjectPtr<UStaticMeshComponent> BoardMesh;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Board)
	FText BoardID;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Board)
	UMaterialInterface* BoardMaterial;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Board)
	TArray<FText> CorrectLinkCompletionOrder;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Board)
	TArray<FText> CompletedLinks;
};
