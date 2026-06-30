// Source/Public/CPP_DialogueAudio.h

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EventTagsStruct.h"
#include "CPP_DialogueAudio.generated.h"


UCLASS()
class HELICONUNREAL_API ACPP_DialogueAudio : public AActor
{
	GENERATED_BODY()
	
private:
	UFUNCTION()
	void HandleOnLineWritten(FEventTagsStruct EventTags);
	
public:	
	// Sets default values for this actor's properties
	ACPP_DialogueAudio();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UFUNCTION(BlueprintImplementableEvent)
	void OnLongLineWritten();
	
	UFUNCTION(BlueprintImplementableEvent)
	void OnMediumLineWritten();
	
	UFUNCTION(BlueprintImplementableEvent)
	void OnShortLineWritten();


};
