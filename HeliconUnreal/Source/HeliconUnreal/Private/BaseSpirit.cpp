#include "BaseSpirit.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/MaterialInterface.h"
#include "Engine/StaticMesh.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"

ABaseSpirit::ABaseSpirit()
	: Time(0)
{
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	SphereMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SphereMeshComponent"));
	SphereMesh->SetupAttachment(RootComponent);

	if (MeshAsset) {
		SphereMesh->SetStaticMesh(MeshAsset);
	}

	if (NiagaraComponent) {

	}
	NiagaraComponent = CreateDefaultSubobject<UNiagaraComponent>(TEXT("NiagaraComp"));
	NiagaraComponent->SetupAttachment(RootComponent);
	NiagaraComponent->bAutoActivate = false;
}

void ABaseSpirit::BeginPlay()
{
	Super::BeginPlay();

	InitialLocation = GetActorLocation();

	if (SphereMesh) {
		SphereMesh->SetMaterial(0, SpiritMaterial);
	}

	DynamicMaterial = SphereMesh->CreateAndSetMaterialInstanceDynamic(0);
	if (DynamicMaterial) {
		DynamicMaterial->SetVectorParameterValue(TEXT("Color"), GlobalSpiritColor);
	}

	if (NiagaraComponent && NiagaraEffect)
	{
		NiagaraComponent->SetAsset(NiagaraEffect);
		NiagaraComponent->Activate(true);
		NiagaraComponent->SetVariableLinearColor(TEXT("User.ParticleColor"), GlobalSpiritColor);
	}
}

void ABaseSpirit::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Time = DeltaTime;

	// Test 
	OnIdle();

}

void ABaseSpirit::OnIdle() {
	YAxisRotation();
	YAxisFloating();
}

void ABaseSpirit::YAxisRotation() {
	float YOffset = FMath::Sin(Time * RotationSpeed) * RotationAmp;

	FRotator NewY = GetActorRotation();
	NewY.Pitch = YOffset;

	SetActorRotation(NewY);
}

void ABaseSpirit::YAxisFloating() {
	float YOffset = FMath::Sin(Time * FloatingSpeed) * FloatingAmp;

	FVector NewY = InitialLocation;
	NewY.Y += YOffset;

	SetActorLocation(NewY);
}

