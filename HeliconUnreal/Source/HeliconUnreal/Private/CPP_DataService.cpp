// CPP_DataService.cpp

#include "CPP_DataService.h"
#include "CPP_HeliconGameInstance.h"
#include "EventTagsStruct.h"

#define LOG_FAILED_CAST UE_LOG(LogTemp, Error, TEXT("DataService failed to get and/or cast game instance"))


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

void UCPP_DataService::IncrementCompletedPuzzles()
{
	CompletedPuzzles++;
	UCPP_HeliconGameInstance* GI = Cast<UCPP_HeliconGameInstance>(GetWorld()->GetGameInstance());
	
	if (GI)
	{
		FEventTagsStruct TagStruct;
		TArray<FName> _TagsList;
		_TagsList.Add("COMPLETED_PUZZLES");
		TagStruct.TagsList = _TagsList;
		
		GI->EventRelay->NotifyPuzzleCompleted(TagStruct);
		return;
	}
	LOG_FAILED_CAST;
}

void UCPP_DataService::SetSlidingPuzzleIsSolved(bool value)
{
	bSlidingPuzzleIsSolved = value;
	UCPP_HeliconGameInstance* GI = Cast<UCPP_HeliconGameInstance>(GetWorld()->GetGameInstance());
	
	if (GI)
	{
		FEventTagsStruct TagStruct;
		TArray<FName> _TagsList;
		_TagsList.Add("SLIDING_PUZZLE");
		TagStruct.TagsList = _TagsList;
		
		GI->EventRelay->NotifyPuzzleCompleted(TagStruct);
		return;
	}
	
}

void UCPP_DataService::AddItemToInventory(FInventoryItemStruct ItemStruct)
{
	for (FInventoryItemStruct item : InventoryItems)
	{
		if (item.Name == ItemStruct.Name)
		{
			return;
		}
	}
	InventoryItems.Add(ItemStruct);
	
	UCPP_HeliconGameInstance* GI = Cast<UCPP_HeliconGameInstance>(GetWorld()->GetGameInstance());
	if (GI)
	{
		FEventTagsStruct TS;
		TArray<FName> _TagsList;
		_TagsList.Add("INVENTORY");
		TS.TagsList = _TagsList;
		GI->EventRelay->NotifyGameDataUpdated(TS);
	}
	
}

void UCPP_DataService::SetCrosshairVisible(bool value)
{
	if (value == bCrosshairVisible)
	{
		return;
	}
	bCrosshairVisible = value;
	
	UCPP_HeliconGameInstance* GI = Cast<UCPP_HeliconGameInstance>(GetWorld()->GetGameInstance());
	
	if (GI)
	{
		if (bCrosshairVisible)
		{
			FEventTagsStruct TagStruct;
			TArray<FName> _TagsList;
			_TagsList.Add("SHOW_CROSSHAIR");
			TagStruct.TagsList = _TagsList;
		
			GI->EventRelay->NotifyGameDataUpdated(TagStruct);
			return;
		}
		else
		{
			FEventTagsStruct TagStruct;
			TArray<FName> _TagsList;
			_TagsList.Add("HIDE_CROSSHAIR");
			TagStruct.TagsList = _TagsList;
		
			GI->EventRelay->NotifyGameDataUpdated(TagStruct);
			return;
		}
		
		
	}
}

void UCPP_DataService::SayHello()
{
	UE_LOG(LogTemp, Log, TEXT("Hello data service!"));
}