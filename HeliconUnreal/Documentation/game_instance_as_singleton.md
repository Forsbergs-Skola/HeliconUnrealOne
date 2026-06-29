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

### In C++

First, get the `UCPP_HeliconGameInstance` from the current world context:

```cpp
#include "CPP_HeliconGameInstance.h"

// Get the game instance and cast it to UCPP_HeliconGameInstance
UCPP_HeliconGameInstance* GI = Cast<UCPP_HeliconGameInstance>(GetWorld()->GetGameInstance());
	if (GI) // if the cast sucseeds
	{
		GI->EventRelay->NotifySomethingHappened();
        // ...
	}
	else
	// a cast failure indicates a likely config problem...
	// For example, the Game Instance isn't properly set in the project settings
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to get and/or cast game instance!"));
	}
```

### Blueprint example: Triggering a conversation with `DialogueService`

#### Step 1: Get Game Instance

(TODO: screenshot)

#### Step 2: Call service getters

(TODO: screenshot)

---

### Blueprint example: Reacting to an event managed by `EventRelay`

#### Step 1: Get Game Instance

(TODO: screenshot)

#### Step 2: Call service getters

(TODO: screenshot)

## Summary

- **Singleton pattern** ensures services exist only once per game, accessible everywhere.
- `UCPP_HeliconGameInstance` owns the singleton services.
- C++ and Blueprints both access these services via getter functions on the custom GameInstance.
- This approach is idiomatic in Unreal and simplifies global system management for our game.

---