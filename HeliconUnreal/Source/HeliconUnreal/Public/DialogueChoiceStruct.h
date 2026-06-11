// DialogueChoiceStruct.h

#pragma once

#include "CoreMinimal.h"
#include "EventTagsStruct.h"
//#include "Fonts/SlateFontInfo.h"
#include "DialogueChoiceStruct.generated.h"

USTRUCT(BlueprintType)
struct FDialogueChoiceStruct
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
	FText ChoiceText;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
	FName DestinationRowName;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
	bool bIsQuit = false;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FEventTagsStruct ChoiceTakenTags;
	
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
	//FSlateFontInfo ChoiceFontInfo;
	
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
	//FSlateColor ChoiceFontColor;
	
};
