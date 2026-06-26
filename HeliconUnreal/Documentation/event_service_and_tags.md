# Helicon Unreal — Event System (First Draft)

## Overview

This project uses a lightweight event system to decouple gameplay “services” (systems that *produce* updates) from gameplay actors/components/UI (systems that *react* to updates). Rather than having every consumer keep direct references to every producer—or constantly polling—services broadcast events through a shared relay object.

The result is a **publish/subscribe (pub-sub)** style architecture:

- **Publishers** (e.g., `CPP_DataService`, `CPP_DialogueService`) broadcast events when something meaningful happens.
- **Subscribers** (any C++ class or Blueprint) register callbacks to be notified.
- **Event payloads** can include **event tags**—an arbitrary array of `FName` values that act like hashtags/Steam tags—so listeners can quickly filter what they care about without needing separate event types for every variation.

This document describes the design patterns in use, typical usage, and the purpose of event tags.

---

## Key Files

- `Source/HeliconUnreal/Public/CPP_EventRelay.h`  
- `Source/HeliconUnreal/Private/CPP_EventRelay.cpp`  
  Defines the central relay / aggregator used to register listeners and broadcast events.

- `Source/HeliconUnreal/Public/CPP_DialogueService.h` and `.cpp`  
  Demonstrates “gameplay narrative” events such as conversation start/end, line written, and choice taken.

- `Source/HeliconUnreal/Public/CPP_DataService.h` and `.cpp`  
  Demonstrates “state/data” events such as “game data updated”.

- `EventTagsStruct.h`  
  Defines the event tag payload structure that can be attached to events.

---

## What Problem This Solves

In an introductory Unreal project, it’s very common to start with tightly coupled logic:

- UI widgets directly call into game systems
- Actors keep hard references to other actors/services
- Systems poll each other each tick (“did something change yet?”)

That approach works for very small prototypes, but tends to produce:
- **High coupling** (changing one system forces changes in many others)
- **Hard-to-follow dependencies**
- **Spaghetti event flow** (everything calls everything)
- **Inflexible reuse** (systems are not portable between levels/projects)

This event system improves that by:
- letting services broadcast *facts* (“something changed”, “a line was written”)  
- letting listeners decide *what to do* (update UI, play audio, trigger VFX, etc.)

---

## Design Patterns in Use

### 1) Observer Pattern (Delegates as Observers)
Unreal’s delegate system is essentially the **Observer pattern**:
- Publishers own a delegate (or a set of delegates)
- Observers bind a function
- Publisher broadcasts, observers are invoked

Here, `CPP_DataService` and `CPP_DialogueService` act as publishers.

### 2) Event Aggregator / Event Bus
Rather than each service exposing many delegates and requiring everyone to reference those services directly, an **Event Relay** centralizes routing and subscription. Conceptually:

- A single place to subscribe/unsubscribe
- A single place to broadcast events
- Reduces “everyone depends on everyone” relationships

This is often called an **Event Aggregator** or **Event Bus**.

### 3) Service Locator (GameInstance as Access Point)
Listeners commonly obtain the relevant service through the GameInstance (or a subsystem-like pattern). This is effectively a **Service Locator**:

- “When I get the event, I fetch the `DataService` from the GameInstance and refresh my state.”

This can be a pragmatic choice for small projects and teaching units because it keeps setup simple and avoids introducing a full dependency injection framework.

---

## Core Concept: “Events Announce Change; Listeners Pull Details”

A recurring design choice in this project is that many events are “edge triggers” rather than “full state replication”:

- The event means: **“something happened”**
- The listener’s job is: **“pull the latest state from the appropriate service and update”**

Example:
- `OnGameDataUpdated` fires
- A UI widget receives it
- The UI widget queries `DataService` for the values it displays

Benefits:
- Keeps the event payload small and generic
- Avoids needing a different event for every data field
- Allows many listeners to react differently to the same update

---

## Event Tags (`EventTagsStruct.h`)

### Motivation
A single event like `OnGameDataUpdated` can represent many kinds of changes. If every consumer needed a dedicated delegate, you’d get an explosion of event types:

- `OnInventoryChanged`
- `OnHealthChanged`
- `OnQuestStateChanged`
- `OnCurrencyChanged`
- …

Instead, this system allows attaching **tags**: an array of `FName` values carrying arbitrary metadata.

Think of tags like:
- hashtags on social media
- Steam store tags
- labels on a message

### How Tags Work
A publisher broadcasts an event and includes a tag list like:

- `["INVENTORY", "ITEM_ADDED"]`
- `["DIALOGUE", "LINE", "LAUGH"]`
- `["SAVEGAME", "LOADED"]`

Subscribers can:
1. receive the event
2. check whether required tags are present
3. ignore the event if it’s irrelevant

### Example Use Case: Filtering Updates
A HUD widget that only cares about inventory might do:

- Subscribe to `OnGameDataUpdated`
- In the callback: if tags contain `"INVENTORY"` → refresh inventory UI  
- Otherwise ignore

This keeps the number of event types low while still allowing specialization.

### Example Use Case: Dialogue “Laugh Track”
When a dialogue line is written, the dialogue service can include a `"LAUGH"` tag for certain lines.

- Dialogue service fires: “line written”
- Payload tags include `"LAUGH"`
- Audio service listens for “line written”
- If tags contain `"LAUGH"` → play sitcom laugh SFX

No direct dependency between dialogue and audio is required.

### Suggested Tag Conventions (Project-Level)
To keep tags maintainable, it helps to adopt conventions:

- Use **UPPER_SNAKE_CASE** for tags (`"LAUGH"`, `"INVENTORY"`)
- Prefer a small “namespace-like” first tag:
  - `"DATA"` / `"DIALOGUE"` / `"AUDIO"`
- Optionally include action tags:
  - `"UPDATED"`, `"STARTED"`, `"ENDED"`, `"CHOICE_TAKEN"`

The project can remain flexible (tags are “arbitrary”), while still readable.

---

## How Services Use Events

### DataService (`CPP_DataService`)
Typical responsibilities:
- Owns game state / player state / runtime data
- Provides getters/setters or mutation functions
- When state changes, broadcasts `OnGameDataUpdated` with relevant tags

Conceptual flow:

1. Some gameplay code updates data via `DataService`
2. `DataService` modifies internal data
3. `DataService` broadcasts `OnGameDataUpdated(tags)`
4. UI/actors receive it and pull updated values from `DataService`

This means:
- DataService does **not** need references to every widget/actor that displays data
- Consumers update on-demand and only when necessary

### DialogueService (`CPP_DialogueService`)
Typical responsibilities:
- Controls conversation lifecycle
- Emits events such as:
  - conversation started
  - conversation ended
  - line written (line delivered to the player)
  - dialogue choice taken

Conceptual flow:

1. Dialogue begins → broadcast “ConversationStarted”
2. Each time a line is produced → broadcast “LineWritten” (with tags like `"LAUGH"`, `"ANGRY"`, etc.)
3. Player chooses a response → broadcast “ChoiceTaken”
4. Dialogue ends → broadcast “ConversationEnded”

This enables:
- UI to update the subtitle box
- audio to play voice / SFX based on tags
- achievements/telemetry to record choice outcomes
without any of those systems being hardwired into DialogueService.

---

## Why an Event Relay Instead of Direct Delegates on Each Service?

Unreal supports direct delegates on a service class, and that can be fine. The relay approach provides a teaching-friendly middle ground:

**Benefits**
- **Centralized subscription management**  
  Easier to find “what listens to what” by searching for relay subscriptions.
- **Reduced dependency graph**  
  Subscribers can listen without needing strong references to each service instance.
- **Easier to add new listeners**  
  Add a new system (e.g., an `AudioService`) that listens to existing events without modifying the publisher.
- **Supports “meta-events”**  
  Tag filtering becomes a natural extension.

**Tradeoffs**
- **Harder to trace at runtime** compared to direct method calls (events are indirect)
- Must be disciplined about:
  - unsubscribing when objects are destroyed
  - avoiding broadcasting too frequently (event spam)
  - choosing clear tag conventions

---

## Recommended Usage Patterns

### 1) Subscribe in BeginPlay / Initialize, Unsubscribe in EndPlay / Deinitialize
To prevent calling into destroyed objects:
- Bind when the object becomes valid
- Unbind when it is being torn down

(Exact API depends on `CPP_EventRelay` implementation.)

### 2) Keep Event Callbacks Lightweight
Callbacks should typically:
- check tags (fast filter)
- pull state from a service
- update local/UI state

Avoid heavy logic in the callback if the event can fire frequently.

### 3) Prefer “Pull” for Large State, “Push” for Small Context
Good uses of payload:
- tags (`FName` list)
- identifiers (e.g., which conversation, which choice)
- small values

For big state (large structs, arrays), prefer fetching from the service after the event.

---

## Example (Conceptual Pseudocode)

### Subscribing to Data Updates (Listener Side)
```cpp
// Pseudocode only — adjust to actual CPP_EventRelay API

void UInventoryWidget::NativeConstruct()
{
    // Subscribe to OnGameDataUpdated
}

void UInventoryWidget::OnGameDataUpdated(const FEventTags& Tags)
{
    if (!Tags.Contains("INVENTORY"))
        return;

    // Pull state from DataService via GameInstance and rebuild UI
}
```

### Broadcasting from DataService (Publisher Side)
```cpp
// Pseudocode only — adjust to actual CPP_EventRelay API

void UCPP_DataService::AddItem(...)
{
    // mutate internal inventory...

    BroadcastOnGameDataUpdated({ "INVENTORY", "ITEM_ADDED" });
}
```

### Dialogue “Laugh Track” (Audio Listener)
```cpp
// Pseudocode only — adjust to actual CPP_EventRelay API

void UAudioService::OnDialogueLineWritten(const FEventTags& Tags /*, maybe line info */)
{
    if (Tags.Contains("LAUGH"))
    {
        PlayLaughSFX();
    }
}
```

---

## Summary

This event system provides a clean, introductory-friendly way to structure Unreal gameplay code around:
- **services** that own state and emit events
- **listeners** that react without direct dependencies
- **event tags** that add flexible metadata without exploding the number of event types

Conceptually, it combines:
- Observer (delegates)
- Event Aggregator / event bus (relay)
- Service Locator (GameInstance access)

This makes it easier to extend the project—adding new UI, audio behaviors, or analytics—without rewriting existing services.
