#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GullActor.generated.h"

class AADockLightTemplate;
class ADocksPuzzleManager;
class AGullRestPoint;

UENUM(BlueprintType)
enum class EGullState : uint8
{
	Idle,
	MovingToTarget,
	WaitingAtRestPoint,
	Swarming
};

UCLASS()
class HELICONUNREAL_API AGullActor : public AActor
{
	GENERATED_BODY()

public:
	AGullActor();

	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category="Gull")
	bool StartTurn(
		const TArray<AADockLightTemplate*>& Lights,
		ADocksPuzzleManager* InPuzzleManager,
		const TArray<AGullRestPoint*>& RestPoints);

	UFUNCTION(BlueprintCallable, Category="Gull")
	void ResetForPuzzle();

	UFUNCTION(BlueprintPure, Category="Gull")
	EGullState GetGullState() const { return State; }

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Gull")
	float MoveSpeed = 300.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Gull")
	float ArrivalDistance = 50.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Gull")
	float SwarmDuration = 2.f;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category="Gull")
	EGullState State = EGullState::Idle;

protected:
	virtual void BeginPlay() override;

	UPROPERTY()
	FVector StartLocation;

	UPROPERTY()
	FRotator StartRotation;

	UPROPERTY()
	TObjectPtr<AActor> LockedTarget;

	UPROPERTY()
	TObjectPtr<ADocksPuzzleManager> PuzzleManager;

	UPROPERTY()
	float SwarmTimer = 0.f;

	UPROPERTY()
	TObjectPtr<AActor> CurrentWaypoint;

	UPROPERTY()
	TObjectPtr<AActor> NextTarget;

	AADockLightTemplate* FindBestTarget(const TArray<AADockLightTemplate*>& Lights) const;

	AGullRestPoint* FindBlockingRestPoint(
		const FVector& Destination,
		const TArray<AGullRestPoint*>& RestPoints) const;

	void SetTarget(AActor* NewTarget);
	void SetWaypoint(AActor* NewWaypoint);
	void EnterSwarming();
	void FinishTurn();
};
