// CPP_HeliconGameInstance.h
#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "CPP_EventRelay.h"
#include "CPP_HeliconGameInstance.generated.h"

UCLASS()
class HELICONUNREAL_API UCPP_HeliconGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	UCPP_EventRelay* EventRelay;
	
	UFUNCTION()
	virtual void Init() override;
};
