// EventTagsStruct.h

#pragma once

#include "CoreMinimal.h"
#include "EventTagsStruct.generated.h"

USTRUCT(BlueprintType)
struct FEventTagsStruct
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Events")
	TArray<FName> TagsList;
};