# Puzzle Manager

## Overview

The `PuzzleManager` is a central gameplay manager implemented in C++. It is responsible for shared puzzle logic, room state management, and communication between gameplay systems.

Rather than allowing individual Blueprints to communicate directly with one another, they communicate through the `PuzzleManager`.

The `PuzzleManager` acts as one of the project's central gameplay controller.

## Purpose

Many systems depend on the current puzzle state.

Examples include:

- Room lighting
- Radio dialogue
- Ambient audio
- Puzzle progression
- Environmental objects

If each Blueprint referenced every other Blueprint directly, the project would become difficult to maintain and extend.

The `PuzzleManager` removes these dependencies by acting as the single source of truth.

## Responsibilities

The `PuzzleManager` is responsible for:

- Storing the current room state.
- Switching between a rooms State A and State B.
- Tracking puzzle progression.
- Broadcasting room state changes.
- Providing shared gameplay information.

## Design Pattern

### Observer Pattern

The `PuzzleManager` exposes an Event Dispatcher named `OnRoomStateChanged`.

Instead of constantly checking whether the room state has changed, interested Blueprints subscribe to this dispatcher.

Whenever the room state changes, the `PuzzleManager` broadcasts the new state and every subscribed Blueprint updates automatically.

## System Flow

1. Player interacts with `BP_StateSwitch`.
2. `BP_StateSwitch` calls the `PuzzleManager`.
3. `PuzzleManager` toggles the room state.
4. `PuzzleManager` broadcasts `OnRoomStateChanged`.
5. Listening Blueprints update themselves.

## Advantages

- Centralised puzzle management.
- No hard Blueprint references.
- Easy to expand with additional puzzles.
- Reusable C++ gameplay manager.
- Simplifies communication between systems.
