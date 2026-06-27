#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/EngineTypes.h"
#include "Interactable.h"
#include "SpotlightActor.generated.h"

class AADockLightTemplate;
class ADocksPuzzleManager;

UCLASS()
class HELICONUNREAL_API ASpotlightActor : public AActor, public IInteractable
{
	GENERATED_BODY()

public:
	ASpotlightActor();

	virtual void Tick(float DeltaTime) override;
	virtual void Interact_Implementation() override;

	UFUNCTION(BlueprintCallable, Category="Spotlight")
	void ResetForPuzzle();

	void RegisterPuzzleManager(ADocksPuzzleManager* InPuzzleManager);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Spotlight")
	float RequiredHoldTime = 3.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Spotlight")
	float TraceDistance = 2000.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Spotlight")
	bool bDrawDebugTrace = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Spotlight")
	TEnumAsByte<ECollisionChannel> TraceChannel = ECC_Visibility;

	UPROPERTY(BlueprintReadWrite, Category="Spotlight")
	bool bIsControlled = false;

protected:
	UPROPERTY()
	TObjectPtr<AADockLightTemplate> CurrentTarget;

	UPROPERTY()
	float ContactTime = 0.f;

	UPROPERTY()
	TObjectPtr<ADocksPuzzleManager> PuzzleManager;

	AADockLightTemplate* FindUnlitLightAlongTrace(const FVector& Start, const FVector& End, bool& bOutHit) const;
};
