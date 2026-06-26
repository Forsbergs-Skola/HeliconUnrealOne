#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ADockLightTemplate.h"
#include "GullActor.h"
#include "DocksPuzzleManager.generated.h"

UENUM(BlueprintType)
enum class EDocksPuzzleTurn : uint8
{
	Player     UMETA(DisplayName="Player"),
	Gulls      UMETA(DisplayName="Gulls"),
	Resolving  UMETA(DisplayName="Resolving"),
	Complete   UMETA(DisplayName="Complete")
};

UCLASS()
class HELICONUNREAL_API ADocksPuzzleManager : public AActor
{
	GENERATED_BODY()
	
public:	
	ADocksPuzzleManager();

protected:
	virtual void BeginPlay() override;

public:	
	UPROPERTY(BlueprintReadOnly)
	EDocksPuzzleTurn CurrentTurn;

	UPROPERTY(BlueprintReadOnly)
	bool bPuzzleComplete;

	UFUNCTION(BlueprintCallable)
	void StartPlayerTurn();

	UFUNCTION(BlueprintCallable)
	void StartGullTurn();

	UFUNCTION(BlueprintCallable)
	void EndPlayerTurn();

	UFUNCTION(BlueprintCallable)
	void EndGullTurn();

	UFUNCTION(BlueprintCallable)
	void CheckWinCondition();

	UFUNCTION(BlueprintCallable)
	void ResetPuzzle();

	UFUNCTION(BlueprintImplementableEvent)
	void BP_PlayerTurnStarted();

	UFUNCTION(BlueprintImplementableEvent)
	void BP_GullTurnStarted();

	UFUNCTION(BlueprintImplementableEvent)
	void BP_PuzzleCompleted();

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite)
	TArray<AADockLightTemplate*> PuzzleLights;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite)
	TArray<AGullActor*> Gulls;

};

