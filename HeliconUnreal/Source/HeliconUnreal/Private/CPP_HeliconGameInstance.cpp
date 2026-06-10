// CPP_HeliconGameInstance.cpp 

#include "CPP_HeliconGameInstance.h"
#include "K2Node_ConstructObjectFromClass.h"

void UCPP_HeliconGameInstance::Init()
{
	// Say hi
	UE_LOG(LogTemp, Log, TEXT("HELLO Game Instance!"))
	
	// Create the EventRelay
	EventRelay = NewObject<UCPP_EventRelay>(this, UCPP_EventRelay::StaticClass());
	EventRelay->SayHello();
}
