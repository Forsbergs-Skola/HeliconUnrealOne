# Dialogue System

## Purpose / High-level overview
The dialogue system in this project is split into two responsibilities:

1. **C++ “service” layer (lightweight state + signaling)**
   - Starts and ends conversations.
   - Stores which conversation is currently active.
   - Exposes a “dialogue active” boolean.
   - Relies on project event wiring ([an event relay](./event_service_and_tags.md) ) to notify UI.

2. **UI Widget Blueprint layer (full conversation runtime)**
   - Displays the current line of dialogue.
   - Advances through rows in the data table.
   - Presents choices to the player.
   - Applies UI styling (fonts/colors) from the conversation struct.
   - Reacts to “conversation started” / “conversation ended” events.

This document focuses on the authoring workflow and how to trigger conversations. 

---

## Minimal “how to use” summary
- Make a Data Table using `FDialogueLineStruct`.
- Put that Data Table into a `FDialogueConvoStruct`.
- Put that struct on an actor as an instance-editable variable.
- On trigger: `GameInstance -> DialogueService -> StartConvo(ConvoStruct)`.
- UI hears “convo started” and takes it from there, managing the dialogue presentation and triggering `EndConvo()` at the appropriate time.

---

## Key types (C++ structs / classes)

### `FEventTagsStruct` (`EventTagsStruct.h`)
```cpp
USTRUCT(BlueprintType)
struct FEventTagsStruct
{
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Events")
  TArray<FName> TagsList;
};
```

**What it represents:**  
A simple container for “event tags” (`FName`s) that can be attached to dialogue events (conversation start, conversation end, line written, choice taken).

**Why it exists:**  
It provides a lightweight way for dialogue content to emit “what happened” markers that other systems can listen for (progression flags, narrative state, analytics, etc.). The exact meaning of each tag is content-defined.

---

### `FDialogueChoiceStruct` (`DialogueChoiceStruct.h`)
Represents a single player choice.

Relevant fields:
- `ChoiceText` — what the player sees.
- `DestinationRowName` — which row to jump to if chosen.
- `bIsQuit` — whether this choice exits the conversation.
- `ChoiceTakenTags` — tags emitted when this choice is taken.

---

### `FDialogueLineStruct` (`DialogueLineStruct.h`)
This is the **row structure** used by the conversation’s `UDataTable`.

Relevant fields:
- `SpeakerName` — displayed name.
- `DialogueText` — displayed line text.
- `NextRowName` — default next row (for non-choice advancement).
- `Choices` — array of `FDialogueChoiceStruct` (if present, UI should present choices).
- `bIsQuit` — whether the conversation should end on this line.
- `bShowPortrait`, `PortraitTexture` — optional portrait support.
- `LineWrittenTags` — tags emitted when this line is displayed.

---

### `FDialogueConvoStruct` (`DialogueConvoStruct.h`)
This is the **conversation “definition”** you assign in the editor to actors that can start dialogue.

Relevant fields:
- `ConvoLinesTable` (`UDataTable*`) — the data table containing all `FDialogueLineStruct` rows.
- `ConvoStartedTags` / `ConvoEndedTags` — tags emitted when the convo begins/ends.
- Appearance fields — fonts/colors for speaker name, line text, choices, next button, etc.

---

### `UCPP_DialogueService` (`CPP_DialogueService.h`)
A UObject that represents the current dialogue state at a [**game-instance level**](./game_instance_as_singleton.md).

Relevant fields:
- `CurrentConvo` (`FDialogueConvoStruct`) — the currently active conversation definition.
- `bDialogueActive` — whether a conversation is active.

Relevant functions:
- `StartConvo(FDialogueConvoStruct Convo)`
- `EndConvo()`

**Important:**  
The service does **not** run the conversation flow (row navigation, choice logic, UI display). It acts as the “entry/exit + shared state” point that the UI reacts to.

---

## Authoring workflow (Editor)

### Step 1: Create a Data Table for the conversation
1. In the Unreal Editor, create a **Data Table** asset.
2. Set the **Row Structure** to: `DialogueLineStruct` (`FDialogueLineStruct`).
3. Add rows:
   - Each row name (the key in the Data Table) is used for navigation via:
     - `NextRowName`
     - `DestinationRowName` in choices

**Recommended authoring conventions**
- The first line of any conversation **MUST** be `START`. This tells the UI what line to serve up first.
- Use consistent row naming for the rest, e.g.:
  - `001`, `002`, `CHOICE_A`, `END`
- Ensure every `NextRowName` or `DestinationRowName` points to a valid row name (unless intentionally ending).

---

### Step 2: Prepare a `FDialogueConvoStruct`
A conversation is represented by a `FDialogueConvoStruct` value, usually stored as a variable on an actor.

Set:
- `ConvoLinesTable` → your Data Table asset from Step 1
- Optional: fonts/colors for UI styling
- Optional: `ConvoStartedTags` / `ConvoEndedTags`

---

## Triggering a conversation (Blueprint usage)

### Typical setup: “Dialogue trigger” actor
Common examples:
- Box collision trigger volume
- Interactable actor (button press)
- NPC actor with interaction

**Workflow:**
1. Add a variable to the actor blueprint:
   - Type: `DialogueConvoStruct`
   - Name suggestion: `ConvoToStart`
2. Make it editable per-instance:
   - Mark **Instance Editable** (the “eyeball” icon), so it can be set from the Outliner.
3. In the level, select the actor instance and assign:
   - `ConvoToStart.ConvoLinesTable` to the desired Data Table
   - (optional) any appearance/tags fields

### Trigger logic (conceptual Blueprint)
When “your thing happens” (overlap, interact, etc.):

1. Get Game Instance
2. Cast to `CPP_HeliconGameInstance`
3. Get `DialogueService`
4. Call `StartConvo(ConvoToStart)`

That is the entire entry point expected by the dialogue system.

---

## Conversation runtime (what happens after `StartConvo`)
Once `StartConvo` is called:

- `UCPP_DialogueService` stores the passed `FDialogueConvoStruct` in `CurrentConvo`.
- `bDialogueActive` becomes `true`.
- The project’s UI layer listens for the “OnConvoStarted” event via the event relay.
- The UI widget then:
  - Reads the `ConvoLinesTable`
  - Displays the first line (i.e. the one whose row name is `START`)
  - Advances through `NextRowName`
  - Presents `Choices` when present
  - Ends when a line/choice indicates quit (`bIsQuit`) or when the service is told to end

When conversation ends:
- `EndConvo()` is called
- `bDialogueActive` becomes `false`
- The UI hides/cleans up
- “Convo ended” events/tags can be emitted

---

## Event tags (how to use `FEventTagsStruct`)
Several dialogue elements can carry tags:

- `FDialogueConvoStruct.ConvoStartedTags`
- `FDialogueConvoStruct.ConvoEndedTags`
- `FDialogueLineStruct.LineWrittenTags`
- `FDialogueChoiceStruct.ChoiceTakenTags`

**Intended use:**  
Tags serve as lightweight “signals” about narrative progression or player actions.

**Examples (content-defined)**
- `Met_NPC_Bob`
- `Quest01_Accepted`
- `Heard_Rumor_About_Cave`
- `Choice_Spared_Enemy`