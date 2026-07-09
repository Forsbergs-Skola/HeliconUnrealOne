// CPP_DialogueService.cpp


#include "CPP_DialogueService.h"
#include "EventTagsStruct.h"
#include "CPP_HeliconGameInstance.h"
#include "CPP_EventRelay.h"

void UCPP_DialogueService::StartConvo(FDialogueConvoStruct Convo)
{
	if (bDialogueActive)
	{
		UE_LOG(LogTemp, Warning, TEXT("A dialogue is already active!!"));
		return;
	}
	CurrentConvo = Convo;
	bDialogueActive = true;
	FEventTagsStruct Tags = CurrentConvo.ConvoStartedTags;
	UCPP_HeliconGameInstance* GI = Cast<UCPP_HeliconGameInstance>(GetWorld()->GetGameInstance());
	if (GI)
	{
		GI->EventRelay->NotifyConvoStarted(Tags);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("DialogueService failed to get and/or cast game instance"));
	}
}

void UCPP_DialogueService::EndConvo()
{
	if (!bDialogueActive)
	{
		UE_LOG(LogTemp, Warning, TEXT("What dialogue?"));
		return;
	}
	bDialogueActive = false;
	FEventTagsStruct Tags = CurrentConvo.ConvoEndedTags;
	UCPP_HeliconGameInstance* GI = Cast<UCPP_HeliconGameInstance>(GetWorld()->GetGameInstance());
	if (GI)
	{
		GI->EventRelay->NotifyConvoEnded(Tags);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("DialogueService failed to get and/or cast game instance"));
	}
	
}

void UCPP_DialogueService::SayHello()
{
	UE_LOG(LogTemp, Log, TEXT("Dialogue manager says hello!"));
}

