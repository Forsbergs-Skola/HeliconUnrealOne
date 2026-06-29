#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BoardPuzzleListener.generated.h"

class ABoardPuzzleBoard;
class UCPP_HeliconGameInstance;
struct FEventTagsStruct;

UCLASS()
class HELICONUNREAL_API ABoardPuzzleListener : public AActor
{
	GENERATED_BODY()
	
public:	
	ABoardPuzzleListener();
	
	UPROPERTY(EditAnywhere, BLueprintReadWrite, Category = "Listener")
	bool bImplementInBlueprint;
	
	UFUNCTION(BlueprintImplementableEvent)
	void OnCapturedEvent(FEventTagsStruct TagsStruct);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Listener")
	TObjectPtr<ABoardPuzzleBoard> Board;
protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	
private:
	void BindEvent(UCPP_HeliconGameInstance* GameInstance);

};
