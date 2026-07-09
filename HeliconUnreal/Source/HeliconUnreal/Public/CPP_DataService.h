// CPP_DataService.h

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "InventoryItemStruct.h"
#include "CPP_DataService.generated.h"

// Every game datum managed by this service must have the following:
//
// 1) a public UPROPERTY(VisibleAnywhere, BlueprintReadOnly) to hold the data
// 2) a public UFUNCTION(BlueprintCallable) function to update the data
// 3) the implementation of that function must call NotifyGameDataUpdated(FEventTagsStruct TagsStruct)
//      and provide an EventTagsStruct (even if the tags list is empty)
//
// See int SecondsPlayed / SetSecondsPlayed(int value) for an example.


UCLASS()
class HELICONUNREAL_API UCPP_DataService : public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int SecondsPlayed;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int CompletedPuzzles;
	
	// There will be a pickup somewhere that is only enabled if this is true.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bSlidingPuzzleIsSolved;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<FInventoryItemStruct> InventoryItems;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bCrosshairVisible;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int FinalQuestionsAnswered = 0;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int FinalWrongAnswers = 0;
	
	UFUNCTION(BlueprintCallable)
	void SetSecondsPlayed(int value);
	
	UFUNCTION(BlueprintCallable)
	void IncrementCompletedPuzzles();
	
	UFUNCTION(BlueprintCallable)
	void SetSlidingPuzzleIsSolved(bool value);
	
	UFUNCTION(BlueprintCallable)
	void AddItemToInventory(FInventoryItemStruct ItemStruct);
	
	UFUNCTION(BlueprintCallable)
	void SetCrosshairVisible(bool value);
	
	UFUNCTION(BlueprintCallable)
	void IncrementFinalQuestionsAnswered();
	
	UFUNCTION(BlueprintCallable)
	void IncrementFinalWrongAnswers();
	
	UFUNCTION(BlueprintCallable)
	void SayHello();
};
