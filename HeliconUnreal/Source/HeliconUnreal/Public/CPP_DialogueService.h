// CPP_DialogueService.h

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "DialogueConvoStruct.h"
#include "CPP_DialogueService.generated.h"


UCLASS()
class HELICONUNREAL_API UCPP_DialogueService : public UObject
{
	GENERATED_BODY()
	
public:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FDialogueConvoStruct CurrentConvo;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool bDialogueActive = false;
	
	
	UFUNCTION(BlueprintCallable)
	void StartConvo(FDialogueConvoStruct Convo);
	
	UFUNCTION(BlueprintCallable)
	void EndConvo();
	
	
	UFUNCTION(BlueprintCallable)
	void SayHello();
	
	
};
