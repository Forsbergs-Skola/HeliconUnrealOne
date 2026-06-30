// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PuzzleManager.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(
	FOnRoomStateChanged,
	bool,
	bStateB
);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPuzzleUnlocked);

UCLASS()
class HELICONUNREAL_API APuzzleManager : public AActor
{
	GENERATED_BODY()

public:
	
	APuzzleManager();
	
	UPROPERTY(BlueprintReadOnly)
	bool bStateB;
	
	UPROPERTY(BlueprintAssignable)
	FOnRoomStateChanged OnRoomStateChanged;
	
	UFUNCTION(BlueprintCallable)
	void ToggleRoomState();
	
	UPROPERTY(BlueprintAssignable)
	FOnPuzzleUnlocked OnPuzzleUnlocked;
	
	UPROPERTY(BlueprintReadOnly)
	int32 ActivatedObjects = 0;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	int32 RequiredObjects = 3;
	
	UFUNCTION(BlueprintCallable)
	void RegisterActivatedObject();
};

