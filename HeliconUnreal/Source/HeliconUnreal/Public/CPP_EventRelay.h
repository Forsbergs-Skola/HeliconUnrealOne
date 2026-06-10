// CPP_EventRelay.h

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "CPP_EventRelay.generated.h"

/////////////////////
// Event Delegates //
/////////////////////

// A bullshit event delegate for testing and demonstration. Delete later.
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSomethingHappened);
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
	
	// A bullshit event dispatcher for testing and demonstration. Delete later.
	UPROPERTY(BlueprintAssignable)
	FOnSomethingHappened OnSomethingHappened;
	
	// and so on...
	// ...
	
	///////////////
	// Notifiers // <- Call on the trigger side
	///////////////
	
	// A bullshit notifier function for testing and demonstration. Delete later.
	UFUNCTION(BlueprintCallable)
	void NotifySomethingHappened();
	
	UFUNCTION()
	void SayHello();
};
