// StateMachineComponent.h

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "StateMachineComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStateEntered, FName, EnteredState);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStateExited, FName, ExitedState);

USTRUCT(BlueprintType)
struct FTransitionsStruct
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, category = "Transitions")
	FName FromStateName;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, category = "Transitions")
	TArray<FName> ToStateNames;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HELICONUNREAL_API UStateMachineComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UStateMachineComponent();
	
	UPROPERTY(BlueprintAssignable)
	FOnStateEntered OnStateEntered;
	UPROPERTY(BlueprintAssignable)
	FOnStateExited OnStateExited;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "StateMachineComponent")
	FName CurrentState = FName("NONE");
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "StateMachineComponent")
	TArray<FName> StateHistory;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "StateMachineComponent | States")
	int32 StateHistorySize = 10;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "StateMachineComponent | States")
	FName StartingState;
		
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "StateMachineComponent | States")
	TArray<FName> StateList;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "StateMachineComponent | Transitions")
	TArray<FTransitionsStruct> Transitions;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// NOTE: tick disabled in constructor
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	UFUNCTION(BlueprintCallable, Category = "StateMachineComponent")
	bool RequestTransition(FName ToState);
	
private:
	void GroomStateHistory();
};
