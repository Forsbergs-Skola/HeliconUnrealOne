# Tutorial Puzzle

## Overview

The Tutorial Puzzle introduces the game's interaction mechanics to the player.

Instead of relying on written instructions, the player learns how interaction and puzzle progression work through gameplay.

## Purpose

The tutorial functions as an onboarding experience.

It teaches the player how to:

- Identify interactable objects.
- Interact with gameplay objects.
- Understand puzzle progression.
- Recognise visual interaction cues.

## System Flow

1. A barrier blocks the player's path.
2. Three objects are initially interactable.
3. Each interaction is registered by the `PuzzleManager`.
4. Once all three objects have been activated, a fourth object becomes interactable.
5. The fourth object's Point Light becomes visible, indicating the next objective.
6. The player interacts with the final object.
7. The barrier is removed.
8. Weather and dialogue events are triggered.
9. The player may continue.

## Puzzle Logic

Each tutorial object reports its activation to the `PuzzleManager`.

Once the required number of activated objects has been reached, the `PuzzleManager` unlocks the final interaction.

Keeping this logic inside the `PuzzleManager` prevents individual objects from needing to communicate directly with one another.

## Advantages

- Introduces interaction mechanics naturally.
- Teaches puzzle progression through gameplay.
- Reuses the existing Interaction System.
- Easily expandable for future onboarding puzzles.
