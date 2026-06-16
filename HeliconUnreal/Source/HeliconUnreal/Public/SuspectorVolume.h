// Putting this class on hold since it's not that useful 

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SuspectorVolume.generated.h"

UCLASS()
class HELICONUNREAL_API ASuspectorVolume : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASuspectorVolume();
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="SuspectorVolume|Mesh")
	TArray<TObjectPtr<UStaticMesh>> StaticMeshes;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="SuspectorVolume|Blocking Volume")
	TObjectPtr<AActor> BlockingVolume;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="SuspectorVolume|Blocking Volumes")
	float SpawnOffsetFromBlockingVolume; 

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void OnConstruction(const FTransform& Transform) override;

public:	
	// Called every frame
	
	virtual void Tick(float DeltaTime) override;

private:	
	
	FVector VolumeScale;
	
	void SpawnSuspectorActors(); 
};
