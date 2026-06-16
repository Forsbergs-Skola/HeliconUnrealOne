// CPP_EventRelay.cpp

#include "CPP_EventRelay.h"

void UCPP_EventRelay::SayHello()
{
	UE_LOG(LogTemp, Log, TEXT("Hello world from the EventRelay!"));
}

void UCPP_EventRelay::NotifySomethingHappened()
{
	OnSomethingHappened.Broadcast();
}

void UCPP_EventRelay::NotifyGameDataUpdated(FEventTagsStruct TagsStruct)
{
	OnGameDataUpdated.Broadcast(TagsStruct);
}

void UCPP_EventRelay::NotifyPuzzleCompleted(FEventTagsStruct TagsStruct)
{
	OnPuzzleCompleted.Broadcast(TagsStruct);
}

void UCPP_EventRelay::NotifyConvoStarted(FEventTagsStruct TagsStruct)
{
	OnConvoStarted.Broadcast(TagsStruct);
}

void UCPP_EventRelay::NotifyConvoEnded(FEventTagsStruct TagsStruct)
{
	OnConvoEnded.Broadcast(TagsStruct);
}

void UCPP_EventRelay::NotifyDialogueLineWritten(FEventTagsStruct TagsStruct)
{
	OnDialogueLineWritten.Broadcast(TagsStruct);
}

void UCPP_EventRelay::NotifyDialogueChoiceTaken(FEventTagsStruct TagsStruct)
{
	OnDialogueChoiceTaken.Broadcast(TagsStruct);
}

void UCPP_EventRelay::NotifySwitchPuzzleActivated(FEventTagsStruct TagsStruct)
{
	OnSwitchPuzzleActivated.Broadcast(TagsStruct);
}

void UCPP_EventRelay::NotifySwitchPuzzleDeactivated(FEventTagsStruct TagsStruct)
{
	OnSwitchPuzzleDeactivated.Broadcast(TagsStruct);
}

void UCPP_EventRelay::NotifySlidingPuzzleActivated(FEventTagsStruct TagsStruct)
{
	OnSlidingPuzzleActivated.Broadcast(TagsStruct);
}

void UCPP_EventRelay::NotifySlidingPuzzleDeactivated(FEventTagsStruct TagsStruct)
{
	OnSlidingPuzzleDeactivated.Broadcast(TagsStruct);
}

void UCPP_EventRelay::NotifySlidingPuzzleSolved(FEventTagsStruct TagsStruct)
{
	OnSlidingPuzzleSolved.Broadcast(TagsStruct);
}
