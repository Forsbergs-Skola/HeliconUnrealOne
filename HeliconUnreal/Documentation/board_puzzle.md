# Board Puzzle System

## Overview

The Board Puzzle System is a node-based interaction system where the player progresses by activating connected nodes. Each node unlocks an associated link, and the board records the order in which links are completed. The puzzle is solved only if the completed sequence matches the predefined solution.

The system is split into several actors, each with a single responsibility. This makes it easy to build different board layouts in the editor while keeping the gameplay logic reusable.

---

# Architecture

The system consists of four actors.

| Class | Responsibility |
|--------|----------------|
| `ABoardPuzzleBoard` | Stores puzzle progress and validates the solution. |
| `ABoardPuzzleNode` | Handles player interaction and puzzle progression. |
| `ABoardPuzzleLink` | Stores the state and visuals of a puzzle connection. |
| `ABoardPuzzleListener` | Receives puzzle completion events. |

---

# Components

## Board

The board manages the overall state of the puzzle.

It stores the expected completion order along with the links the player has already unlocked. Whenever a node activates, its link is registered with the board. When the ending node is reached, the board compares the recorded sequence against the expected solution. If both sequences match, the puzzle is considered complete.

The board is only responsible for tracking puzzle state and validating completion. It does not handle player interaction.

---

## Node

Nodes are the interactive elements of the puzzle.

Each node owns a single link and can optionally depend on other links already being unlocked before it can activate. Starting nodes can always be activated, while normal nodes require their connected links to be unlocked first. Ending nodes perform the final completion check after activating.

If activation succeeds, the node unlocks its owned link, updates the board, and performs any completion logic required.

---

## Link

A link represents a connection between nodes.

Its responsibility is limited to storing whether it is locked or unlocked and updating its material to reflect that state. Each link also exposes a unique identifier that the board uses when validating the completion order.

---

## Listener

The listener connects the board puzzle system to the project's event system.

When the puzzle is completed, the listener receives the broadcast event and exposes it through a Blueprint event. This allows Blueprint logic to react to puzzle completion without introducing direct dependencies on the puzzle actors.

---
# Completion Events

Once the board has validated the puzzle successfully, the ending node broadcasts an event containing the board identifier.

```
BOARD_PUZZLE
BoardID
```

Other systems can listen for this event to unlock gameplay elements, start scripted sequences, or update progression without requiring direct references to the puzzle.

---

# Typical Setup

A board puzzle consists of a single board actor, one or more nodes, and a link associated with each node. Every node references the board it belongs to, while the board defines the required completion order using link identifiers.

Optional listener actors can be placed in the level to respond to completion events through Blueprint or other gameplay systems.

