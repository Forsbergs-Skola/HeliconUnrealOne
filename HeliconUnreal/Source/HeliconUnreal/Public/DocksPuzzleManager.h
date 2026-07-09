#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DocksPuzzleManager.generated.h"

class AADockLightTemplate;
class AGullActor;
class AGullRestPoint;
class ASpotlightActor;

UENUM(BlueprintType)
enum class EDocksPuzzleTurn : uint8
{
	Player     UMETA(DisplayName="Player"),
	Gulls      UMETA(DisplayName="Gulls"),
	Complete   UMETA(DisplayName="Complete")
};

UCLASS()
class HELICONUNREAL_API ADocksPuzzleManager : public AActor
{
	GENERATED_BODY()

public:
	ADocksPuzzleManager();

	UFUNCTION(BlueprintCallable, Category="Puzzle")
	void StartPlayerTurn();

	UFUNCTION(BlueprintCallable, Category="Puzzle")
	void StartGullTurn();

	UFUNCTION(BlueprintCallable, Category="Puzzle")
	void EndPlayerTurn();

	UFUNCTION(BlueprintCallable, Category="Puzzle")
	void EndGullTurn();

	UFUNCTION(BlueprintCallable, Category="Puzzle")
	void NotifyGullTurnStepComplete(AGullActor* Gull);

	UFUNCTION(BlueprintCallable, Category="Puzzle")
	void CheckWinCondition();

	UFUNCTION(BlueprintCallable, Category="Puzzle")
	void ResetPuzzle();

	UFUNCTION(BlueprintPure, Category="Puzzle")
	EDocksPuzzleTurn GetCurrentTurn() const { return CurrentTurn; }

	int32 GetNextActivationOrder();

	UFUNCTION(BlueprintImplementableEvent, Category="Puzzle")
	void BP_PlayerTurnStarted();

	UFUNCTION(BlueprintImplementableEvent, Category="Puzzle")
	void BP_GullTurnStarted();

	UFUNCTION(BlueprintImplementableEvent, Category="Puzzle")
	void BP_PuzzleCompleted();

	UPROPERTY(BlueprintReadOnly, Category="Puzzle")
	EDocksPuzzleTurn CurrentTurn = EDocksPuzzleTurn::Player;

	UPROPERTY(BlueprintReadOnly, Category="Puzzle")
	bool bPuzzleComplete = false;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category="Puzzle")
	TArray<TObjectPtr<AADockLightTemplate>> PuzzleLights;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category="Puzzle")
	TArray<TObjectPtr<AGullActor>> Gulls;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category="Puzzle")
	TArray<TObjectPtr<ASpotlightActor>> Spotlights;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category="Puzzle")
	TArray<TObjectPtr<AGullRestPoint>> RestPoints;

protected:
	virtual void BeginPlay() override;

private:
	void RegisterPuzzleActors();
	void GatherRestPointsIfNeeded();
	void GatherSpotlightsIfNeeded();

	int32 GlobalLightCounter = 0;
	int32 ActiveGullsRemaining = 0;
};
