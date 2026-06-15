#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "EventTagsStruct.h"
//#include "Fonts/SlateFontInfo.h"
#include "DialogueConvoStruct.generated.h"

USTRUCT(BlueprintType)
struct FDialogueConvoStruct
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName ConvoNameName;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UDataTable* ConvoLinesTable;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FEventTagsStruct ConvoStartedTags;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FEventTagsStruct ConvoEndedTags;
	
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Appearance")
	//FSlateFontInfo SpeakerNameFontInfo;
	
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Appearance")
	//FSlateFontInfo DialogueTextFontInfo;
	
};
