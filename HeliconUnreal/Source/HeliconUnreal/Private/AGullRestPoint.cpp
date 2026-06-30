#include "AGullRestPoint.h"
#include "Components/SphereComponent.h"

#if WITH_EDITOR
#include "UObject/UnrealType.h"
#endif

AGullRestPoint::AGullRestPoint()
{
	PrimaryActorTick.bCanEverTick = false;

	BlockingSphere = CreateDefaultSubobject<USphereComponent>(TEXT("BlockingSphere"));
	SetRootComponent(BlockingSphere);
	BlockingSphere->SetSphereRadius(BlockingRadius);
	BlockingSphere->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	BlockingSphere->SetGenerateOverlapEvents(false);
	BlockingSphere->SetHiddenInGame(true);
}

void AGullRestPoint::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	if (BlockingSphere)
	{
		BlockingSphere->SetSphereRadius(BlockingRadius);
	}
}

#if WITH_EDITOR
void AGullRestPoint::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	if (PropertyChangedEvent.GetPropertyName() == GET_MEMBER_NAME_CHECKED(AGullRestPoint, BlockingRadius)
		&& BlockingSphere)
	{
		BlockingSphere->SetSphereRadius(BlockingRadius);
	}
}
#endif
