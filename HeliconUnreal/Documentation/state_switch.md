# State Switch System

## Overview

The State Switch is the primary gameplay mechanic for the switch puzzle, allowing the player to transition between State A and State B.

Rather than directly controlling every affected object, it requests a state change from the `PuzzleManager`.

The `PuzzleManager` then informs every subscribed Blueprint of the state change.

## Purpose

The State Switch changes the overall state of the room.

Examples of affected systems include:

- Radio broadcasts
- Ambient room audio
- Lighting
- Puzzle objects
- Environmental props

Only the room state changes directly.

Every other system reacts independently.

## System Flow

1. The player interacts with the State Switch.
2. The State Switch calls the `PuzzleManager`.
3. The `PuzzleManager` toggles the room state.
4. The `PuzzleManager` broadcasts `OnRoomStateChanged`.
5. Every subscribed Blueprint updates automatically.

Examples include:

- New radio broadcast.
- Different room ambience.
- Different lighting.
- Puzzle objects become active or inactive.

## Advantages

- One interaction updates the entire room.
- New state-dependent objects require no changes to the switch.
- Easy to scale throughout the game.
- Keeps systems modular.
