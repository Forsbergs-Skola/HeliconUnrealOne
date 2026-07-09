// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Interactable.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UInteractable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class HELICONUNREAL_API IInteractable
{
	GENERATED_BODY()

	/**Olle Add*/
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable,Category="Interaction")
	void Interact();
};
