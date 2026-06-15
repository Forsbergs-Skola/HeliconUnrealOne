// StateMachineComponent.cpp

#include "StateMachineComponent.h"

// Sets default values for this component's properties
UStateMachineComponent::UStateMachineComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}


// Called when the game starts
void UStateMachineComponent::BeginPlay()
{
	Super::BeginPlay();

	if (StartingState == NAME_None)
	{
		UE_LOG(LogTemp, Error, TEXT("Initial state not set"));
		return;
	}
	StateHistory.Add(CurrentState);
	CurrentState = StartingState;
	OnStateEntered.Broadcast(CurrentState);
	UE_LOG(LogTemp, Log, TEXT("SM initialized in state: %s"), *CurrentState.ToString());
}


// NOTE: TICK DISABLED IN CONSTRUCTOR!
void UStateMachineComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

bool UStateMachineComponent::RequestTransition(FName RequestedToState)
{
	
	const FTransitionsStruct* MatchingTransition = Transitions.FindByPredicate(
		[this](const FTransitionsStruct& Transition)
		{
			return Transition.FromStateName == CurrentState;
		});
	if (!MatchingTransition)
	{
		UE_LOG(LogTemp, Log, TEXT("Current state not found in Transitions list: %s"), *CurrentState.ToString());
		return false;
	}
	
	for (const auto& AllowedToState : MatchingTransition->ToStateNames)
	{
		if (AllowedToState == RequestedToState)
		{
			StateHistory.Add(CurrentState);
			GroomStateHistory();
			OnStateExited.Broadcast(CurrentState);
			CurrentState = RequestedToState;
			OnStateEntered.Broadcast(CurrentState);
			UE_LOG(LogTemp, Log, TEXT("New current state: %s"), *CurrentState.ToString());
			return true;
		}
	}
	// this is a Log message, and not Warning or Error because there could be 
	// perfectly legit reasons that the state cannot transition, and is expected to
	// happen during normal gameplay from time to time
	UE_LOG(LogTemp, Log, TEXT("Current state has no allowed transition to state %s"), *RequestedToState.ToString());
	return false;
}

void UStateMachineComponent::GroomStateHistory()
{
	if (StateHistory.Num() > StateHistorySize)
	{
		StateHistory.RemoveAt(0);
	}
}