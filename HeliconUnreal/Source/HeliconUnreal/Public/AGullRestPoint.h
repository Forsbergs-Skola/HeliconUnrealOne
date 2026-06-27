#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AGullRestPoint.generated.h"

class USphereComponent;

UCLASS()
class HELICONUNREAL_API AGullRestPoint : public AActor
{
	GENERATED_BODY()

public:
	AGullRestPoint();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Gull")
	float BlockingRadius = 150.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Gull")
	TObjectPtr<USphereComponent> BlockingSphere;

	float GetBlockingRadius() const { return BlockingRadius; }

	virtual void OnConstruction(const FTransform& Transform) override;

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif
};