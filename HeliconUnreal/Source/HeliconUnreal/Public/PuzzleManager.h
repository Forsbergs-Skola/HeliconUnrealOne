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
};

