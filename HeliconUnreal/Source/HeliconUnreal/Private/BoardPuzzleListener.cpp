#include "BoardPuzzleListener.h"
#include "CPP_HeliconGameInstance.h"
#include "BoardPuzzleBoard.h"

ABoardPuzzleListener::ABoardPuzzleListener()
{
	PrimaryActorTick.bCanEverTick = false;
	bImplementInBlueprint = false;
}

void ABoardPuzzleListener::BeginPlay()
{
	Super::BeginPlay();
	UCPP_HeliconGameInstance* GameInstance = Cast<UCPP_HeliconGameInstance>(GetWorld()->GetGameInstance());
	BindEvent(GameInstance);
}

void ABoardPuzzleListener::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABoardPuzzleListener::BindEvent(UCPP_HeliconGameInstance* GameInstance)
{
	if (GameInstance)
	{
		GameInstance->EventRelay->OnGameDataUpdated.AddDynamic(this, &ABoardPuzzleListener::OnCapturedEvent);
	}
}

