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