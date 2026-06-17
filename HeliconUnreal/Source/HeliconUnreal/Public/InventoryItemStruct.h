#pragma once

#include "CoreMinimal.h"
#include "InventoryItemStruct.generated.h"

USTRUCT(BlueprintType)
struct FInventoryItemStruct
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	FName Name;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	FText DisplayName;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	FText Description;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	UTexture2D* UI_Image;
};
