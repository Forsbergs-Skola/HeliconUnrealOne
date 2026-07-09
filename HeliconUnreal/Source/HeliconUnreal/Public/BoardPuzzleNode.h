#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BoardPuzzleNode.generated.h"

class ABoardPuzzleLink;
class ABoardPuzzleBoard;

UCLASS()
class HELICONUNREAL_API ABoardPuzzleNode : public AActor
{
	GENERATED_BODY()
    
public: 
	ABoardPuzzleNode();
	
	UFUNCTION()
	bool CheckCompletion();
	
	UFUNCTION()
	void NotifyCompletion();
	
	UFUNCTION()
	void UpdateBoard();
	
	UFUNCTION()
	void HandleEndingNode();
	
	UFUNCTION()
	void HandleNormalNode();
	
	UFUNCTION(BlueprintCallable)
    void Reset();

protected:
	virtual void BeginPlay() override;

public: 
	virtual void Tick(float DeltaTime) override;
    
	UFUNCTION(BlueprintCallable)
	void OnNodeClicked(UPrimitiveComponent* ClickedComp, FKey ButtonPressed);
	
	void UnlockLink();
    
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Node")
	TObjectPtr<ABoardPuzzleLink> OwnedLink;
    
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Node")
	TArray<TObjectPtr<ABoardPuzzleLink>> ConnectedLinks;
    
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Node")
	bool bIsStartingNode;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Node")
	bool bIsEndingNode;
    
	UPROPERTY(EditAnywhere, Category = "Node|Visual")
	TObjectPtr<UStaticMeshComponent> NodeMesh;
	
	UPROPERTY(EditAnywhere, Category = "Node")
	TObjectPtr<class UBoxComponent> ClickBox;
    
	UPROPERTY(EditAnywhere, Category = "Node|Visual")
	UMaterialInterface* NodeMaterial;
	
	UPROPERTY(EditAnywhere, Category = "Node|Visual")
	UMaterialInterface* EndingNodeMaterial;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Node")
	TObjectPtr<ABoardPuzzleBoard> Board;
	
  
};