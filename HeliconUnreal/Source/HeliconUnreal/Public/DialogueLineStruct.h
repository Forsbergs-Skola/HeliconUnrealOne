#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "EventTagsStruct.h"
#include "DialogueChoiceStruct.h"
#include "DialogueLineStruct.generated.h"

USTRUCT(BlueprintType)
struct FDialogueLineStruct : public FTableRowBase
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
	FText SpeakerName;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
	FText DialogueText;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
	FName NextRowName;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
	TArray<FDialogueChoiceStruct> Choices;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
	bool bIsQuit;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
	bool bShowPortrait = false;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
	UTexture2D* PortraitTexture;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
	FEventTagsStruct LineWrittenTags;
	
};
