// Source/Private/CPP_DialogueAudio.cpp

#include "CPP_DialogueAudio.h"
#include "CPP_HeliconGameInstance.h"

// Sets default values
ACPP_DialogueAudio::ACPP_DialogueAudio()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACPP_DialogueAudio::BeginPlay()
{
	Super::BeginPlay();
	UCPP_HeliconGameInstance* GI = Cast<UCPP_HeliconGameInstance>(GetWorld()->GetGameInstance());
	if (!GI)
	{
		return;
	}
	
	UCPP_EventRelay* ER = GI->EventRelay;
	if (!ER)
	{
		return;
	}
	
	ER->OnDialogueLineWritten.AddDynamic(this, &ACPP_DialogueAudio::HandleOnLineWritten);
	
}

void ACPP_DialogueAudio::HandleOnLineWritten(FEventTagsStruct EventTags)
{
	// call the BlueprintImplementableEvent
	if (EventTags.TagsList.Contains("LONG"))
	{
		OnLongLineWritten();
	}
	else if (EventTags.TagsList.Contains("MEDIUM"))
	{
		OnMediumLineWritten();
	}
	else if (EventTags.TagsList.Contains("SHORT"))
	{
		OnShortLineWritten();
	}
}

// Called every frame
void ACPP_DialogueAudio::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

