#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BoardPuzzleNode.generated.h"

class ABoardPuzzleLink;

UCLASS()
class HELICONUNREAL_API ABoardPuzzleNode : public AActor
{
	GENERATED_BODY()
	
public:	
	ABoardPuzzleNode();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	
	UFUNCTION(BlueprintCallable)
	void OnNodeHoverBegin(UPrimitiveComponent* TouchedComponent);

	UFUNCTION(BlueprintCallable)
	void OnNodeHoverEnd(UPrimitiveComponent* TouchedComponent);
	
	UFUNCTION(BlueprintCallable)
	void OnHoverTimerComplete() const;
	
	FTimerHandle HoverTimerHandle;
	
	UPROPERTY(EditAnywhere, Category = "Node")
	float RequiredHoverTime = 3.0f;	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Node")
	TObjectPtr<ABoardPuzzleLink> OwnedLink;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Node")
	TObjectPtr<ABoardPuzzleLink> ConnectedLink;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Node")
	bool bIsStartingNode;
	
	UPROPERTY(EditAnywhere, Category = "Node|Visual")
	TObjectPtr<UStaticMeshComponent> NodeMesh;
	
	UPROPERTY(EditDefaultsOnly, Category = "Link|Visual")
	UMaterialInterface* NodeMaterial;
};
