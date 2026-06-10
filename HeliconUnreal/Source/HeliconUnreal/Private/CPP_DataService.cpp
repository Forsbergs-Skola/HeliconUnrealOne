// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_DataService.h"
#include "CPP_HeliconGameInstance.h"
#include "EventTagsStruct.h"


void UCPP_DataService::SetSecondsPlayed(int value)
{
	SecondsPlayed = value;
	UCPP_HeliconGameInstance* GI = Cast<UCPP_HeliconGameInstance>(GetWorld()->GetGameInstance());
	
	if (GI)
	{
		FEventTagsStruct TS;
		TArray<FName> _TagsList;
		_TagsList.Add("SECONDS");
		TS.TagsList = _TagsList;
		GI->EventRelay->NotifyGameDataUpdated(TS);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("DataService failed to get and/or cast game instance"));
	}
}

void UCPP_DataService::SayHello()
{
	UE_LOG(LogTemp, Log, TEXT("Hello data service!"));
}