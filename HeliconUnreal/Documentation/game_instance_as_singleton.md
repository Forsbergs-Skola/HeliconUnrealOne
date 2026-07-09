# Unreal Game Instance As Singleton Solution

## Overview

In this project, we implement the **singleton pattern** in Unreal Engine by extending the `UGameInstance` class, through our custom subclass: `UCPP_HeliconGameInstance`. The singleton pattern ensures that certain services and game-wide managers have only one instance during gameplay, accessible from anywhere in the project (across levels, UI, game logic, etc.).

This document details our singleton implementation and provides usage examples for both C++ and Blueprints.

---

## Why Use GameInstance for Singletons?

- **Persistence**: GameInstance persists across level loads, making it ideal for singletons in Unreal Engine.
- **Access Everywhere**: GameInstance can be accessed from any actor, component, or UI widget.
- **Central Management**: Common services like event relays, dialogue management, or data services are conveniently managed here.

---

## Singleton Services Implemented

### Services Registered in `UCPP_HeliconGameInstance`
- **Event Relay**: Central messaging/event dispatch system (`UCPP_EventRelay`)
- **Dialogue Service**: Handles dialogue trees, conversations (`UCPP_DialogueService`)
- **Data Service**: Manages save/load operations and game data (`UCPP_DataService`)

Located in:

- `Source/HeliconUnreal/Public/CPP_HeliconGameInstance.h`
- `Source/HeliconUnreal/Private/CPP_HeliconGameInstance.cpp`

These services are owned by the GameInstance and instantiated on startup.

---

## Initialization

**Project is configured to use `UCPP_HeliconGameInstance` as the default GameInstance.**

You can confirm this in `DefaultEngine.ini`:

```ini
[/Script/Engine.GameEngine]
GameInstanceClass=/Script/HeliconUnreal.CPP_HeliconGameInstance
```

---

## Accessing Singleton Services

### C++

#### Example 1: Triggering a managed event (CPP_DataService.cpp)

First, get the `UCPP_HeliconGameInstance` from the current world context:

```cpp
#include "CPP_HeliconGameInstance.h"

void UCPP_DataService::SetSecondsPlayed(int value)
{
	SecondsPlayed = value;
	UCPP_HeliconGameInstance* GI = Cast<UCPP_HeliconGameInstance>(GetWorld()->GetGameInstance());
	
	if (GI)
	{
		FEventTagsStruct TS;
		TArray<FName> _TagsList;
		_TagsList.Add("SECONDS");
		TS.TagsList = _TagsList;
		GI->EventRelay->NotifyGameDataUpdated(TS);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("DataService failed to get and/or cast game instance"));
	}
}
```

#### Example 2: Subscribing to a managed event (CPP_DialogueAudio.cpp)

```cpp
#include "CPP_HeliconGameInstance.h"

void ACPP_DialogueAudio::BeginPlay()
{
	Super::BeginPlay();
	UCPP_HeliconGameInstance* GI = Cast<UCPP_HeliconGameInstance>(GetWorld()->GetGameInstance());
	if (!GI)
	{
		return;
	}
	
	UCPP_EventRelay* ER = GI->EventRelay;
	if (!ER)
	{
		return;
	}
	
	ER->OnDialogueLineWritten.AddDynamic(this, &ACPP_DialogueAudio::HandleOnLineWritten);
	
}

void ACPP_DialogueAudio::HandleOnLineWritten(FEventTagsStruct EventTags)
{
	// call the BlueprintImplementableEvent
	if (EventTags.TagsList.Contains("LONG"))
	{
		if (EventTags.TagsList.Contains("MALE"))
		{
			OnMaleLongLineWritten();
		}
		else
		{
			OnFemaleLongLineWritten();
		}
	}
	else if (EventTags.TagsList.Contains("MEDIUM"))
	{
		if (EventTags.TagsList.Contains("MALE"))
		{
			OnMaleMediumLineWritten();
		}
		else
		{
			OnFemaleMediumLineWritten();
		}
	}
	else if (EventTags.TagsList.Contains("SHORT"))
	{
		if (EventTags.TagsList.Contains("MALE"))
		{
			OnMaleShortLineWritten();
		}
		else
		{
			OnFemaleShortLineWritten();
		}
	}
}
```



### Blueprints 

#### Example 1: Starting a dialogue conversation (BP_GenericDialogueTrigger)

![screenshot](start_convo.png)

#### Example 2: Subscribing to a managed event (BP_ConditionalDialogueTrigger)

![screenshot](subscribe.png)

---

## Summary

- **Singleton pattern** ensures services exist only once per game, accessible everywhere.
- `UCPP_HeliconGameInstance` owns the singleton services.
- C++ and Blueprints both access these services via getter functions on the custom GameInstance.
- This approach is idiomatic in Unreal and simplifies global system management for our game.

---