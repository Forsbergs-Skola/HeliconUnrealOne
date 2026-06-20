//Source/HeliconUnreal/Public/DialogueConvoStruct.h

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "EventTagsStruct.h"
#include "Fonts/SlateFontInfo.h"
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
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Appearance")
	FSlateFontInfo SpeakerNameFontInfo;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Appearance")
	FSlateColor SpeakerNameColor;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Appearance")
	FSlateFontInfo LineTextFontInfo;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Appearance")
	FSlateColor LineTextColor;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Appearance")
	FSlateFontInfo ChoiceTextFontInfo;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Appearance")
	FSlateColor ChoiceTextColor;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Appearance")
	FSlateFontInfo NextButtonTextFontInfo;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Appearance")
	FSlateColor NextButtonTextColor;
	
	
	
	
};
