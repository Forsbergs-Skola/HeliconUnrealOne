// CPP_EventRelay.h

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "EventTagsStruct.h"
#include "CPP_EventRelay.generated.h"

/////////////////////
// Event Delegates //
/////////////////////


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPuzzleCompleted, FEventTagsStruct, TagsStruct);

// A bullshit event delegate for testing and demonstration. Delete later.
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSomethingHappened);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGameDataUpdated, FEventTagsStruct, TagsStruct);
// and so on...
// ...

UCLASS()
class HELICONUNREAL_API UCPP_EventRelay : public UObject
{
	GENERATED_BODY()
public:
	
	/////////////////
	// Dispatchers // <- Listen for on the listener side
	/////////////////
	
	UPROPERTY(BlueprintAssignable)
	FOnPuzzleCompleted OnPuzzleCompleted;
	
	// A bullshit event dispatcher for testing and demonstration. Delete later.
	UPROPERTY(BlueprintAssignable)
	FOnSomethingHappened OnSomethingHappened;
	
	UPROPERTY(BlueprintAssignable)
	FOnGameDataUpdated OnGameDataUpdated;
	
	// and so on...
	// ...
	
	///////////////
	// Notifiers // <- Call on the trigger side
	///////////////
	
	// A bullshit notifier function for testing and demonstration. Delete later.
	UFUNCTION(BlueprintCallable)
	void NotifySomethingHappened();
	
	UFUNCTION(BlueprintCallable)
	void NotifyGameDataUpdated(FEventTagsStruct TagsStruct);
	
	UFUNCTION(BlueprintCallable)
	void NotifyPuzzleCompleted(FEventTagsStruct TagsStruct);
	
	UFUNCTION()
	void SayHello();
};
