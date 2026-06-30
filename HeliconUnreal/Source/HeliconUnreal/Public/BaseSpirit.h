#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseSpirit.generated.h"

UCLASS()
class HELICONUNREAL_API ABaseSpirit : public AActor
{
	GENERATED_BODY()
		
public:	
	ABaseSpirit();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Art")
	FLinearColor GlobalSpiritColor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Art|Mesh")
	TObjectPtr<class UStaticMeshComponent> SphereMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Art|Mesh")
	TObjectPtr<class UStaticMesh> MeshAsset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Art|Material")
	TObjectPtr<class UMaterialInstance> SpiritMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadwrite, Category = "Art|VFX")
	TObjectPtr<class UNiagaraComponent> NiagaraComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Art|VFX")
	TObjectPtr<class UNiagaraSystem> NiagaraEffect;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spirit")
	bool bIsFamilyMember; 

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Idle")
	float RotationAmp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Idle")
	float RotationSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Idle")
	float FloatingAmp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Idle")
	float FloatingSpeed;


	UPROPERTY()
	TObjectPtr<class UMaterialInstanceDynamic> DynamicMaterial;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnIdle();

private:
	void YAxisRotation();
	void YAxisFloating();

	FVector InitialLocation;

	float Time;

};
