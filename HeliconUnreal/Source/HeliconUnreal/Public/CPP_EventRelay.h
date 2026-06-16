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
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnConvoStarted, FEventTagsStruct, TagsStruct);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnConvoEnded, FEventTagsStruct, TagsStruct);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDialogueLineWritten, FEventTagsStruct, TagsStruct);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDialogueChoiceTaken, FEventTagsStruct, TagsStruct);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSwitchPuzzleActivated, FEventTagsStruct, TagsStruct);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSwitchPuzzleDeactivated, FEventTagsStruct, TagsStruct);
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
	
	UPROPERTY(BlueprintAssignable)
	FOnConvoStarted OnConvoStarted;
	
	UPROPERTY(BlueprintAssignable)
	FOnConvoEnded OnConvoEnded;
	
	UPROPERTY(BlueprintAssignable)
	FOnDialogueLineWritten OnDialogueLineWritten;
	
	UPROPERTY(BlueprintAssignable)
	FOnDialogueChoiceTaken OnDialogueChoiceTaken;
	
	UPROPERTY(BlueprintAssignable)
	FOnSwitchPuzzleActivated OnSwitchPuzzleActivated;
	
	UPROPERTY(BlueprintAssignable)
	FOnSwitchPuzzleDeactivated OnSwitchPuzzleDeactivated;
	
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
	
	UFUNCTION(BlueprintCallable)
	void NotifyConvoStarted(FEventTagsStruct TagsStruct);
	
	UFUNCTION(BlueprintCallable)
	void NotifyConvoEnded(FEventTagsStruct TagsStruct);
	
	UFUNCTION(BlueprintCallable)
	void NotifyDialogueLineWritten(FEventTagsStruct TagsStruct);
	
	UFUNCTION(BlueprintCallable)
	void NotifyDialogueChoiceTaken(FEventTagsStruct TagsStruct);
	
	UFUNCTION(BlueprintCallable)
	void NotifySwitchPuzzleActivated(FEventTagsStruct TagsStruct);
	
	UFUNCTION(BlueprintCallable)
	void NotifySwitchPuzzleDeactivated(FEventTagsStruct TagsStruct);
	
	UFUNCTION()
	void SayHello();
};
