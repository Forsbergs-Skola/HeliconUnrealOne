// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_BullshitTriggerComponent.h"
#include "CPP_HeliconGameInstance.h"

// Sets default values for this component's properties
UCPP_BullshitTriggerComponent::UCPP_BullshitTriggerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UCPP_BullshitTriggerComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UCPP_BullshitTriggerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UCPP_BullshitTriggerComponent::MakeSomeBullshitHappen()
{
	UCPP_HeliconGameInstance* GI = Cast<UCPP_HeliconGameInstance>(GetWorld()->GetGameInstance());
	if (GI)
	{
		GI->EventRelay->NotifySomethingHappened();
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to get and/or cast game instance!"));
	}
}

