#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ADockLightTemplate.generated.h"

class ADocksPuzzleManager;

UCLASS()
class HELICONUNREAL_API AADockLightTemplate : public AActor
{
	GENERATED_BODY()

public:
	AADockLightTemplate();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Light")
	bool bIsLit;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Puzzle")
	bool bRequiredForWin = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Light")
	bool bIsDecoy = false;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category="Light")
	int32 ActivationOrder = -1;

	UFUNCTION(BlueprintCallable, Category="Light")
	virtual void LightOn();

	UFUNCTION(BlueprintCallable, Category="Light")
	virtual void LightOff();

	UFUNCTION(BlueprintCallable, Category="Light")
	void ResetLightState();

	UFUNCTION(BlueprintImplementableEvent, Category="Light")
	void BP_LightStateChanged(bool bNewIsLit);

	void RegisterPuzzleManager(ADocksPuzzleManager* InPuzzleManager);

protected:
	UPROPERTY()
	TObjectPtr<ADocksPuzzleManager> PuzzleManager;
};
