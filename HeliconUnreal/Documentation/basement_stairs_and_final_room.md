# Basement Stairs and Final Room Documentation

## Overview

The basement sequence is built around an endless looping spiral staircase that acts as a traversal puzzle.

The player moves through the stairs in a repeating space until they solve the puzzle by jumping down the middle of the staircase. That action takes them into the final room.

## Purpose

This section is designed to feel unsettling and directionless at the same time.

The looping stairs create confusion and tension, while the final room acts as the emotional payoff of the entire game, revealing the truth.

## Stair Loop

The staircase is simply two spiral staircase brushes with a trigger collider halfway down. This trigger collider seamlessly teleports them backup, preventing them from ever descending fully.

The fog within the room gets heavier as you descend, acting as a very subtle hint that this staircase is never ending, forcing the player to find another awy down.

Relevant basement assets include:

- `BP_StairsCollider`
- `BP_TeleportTrigger`
- `BP_TeleportLocation`
- `BP_StairsCage`
- `Spiral_Stair_Brush_StaticMesh`

## Puzzle Flow

1. The player enters the spiral staircase.
2. The stairs loop back on themselves.
3. The player discovers that the middle of the spiral is the correct path.
4. Jumping down the middle triggers the cage to lock them in and at the bottom a collider holds the teleport logic.
5. The player is moved to the final room.

This keeps the puzzle simple to understand, but still memorable in presentation.

## Final Room

The final room contains four spirits and a doll in the crib, a very unexpected ending to the game.

This room works as the story payoff and should feel like a final reveal rather than a normal gameplay space.

The final room uses the Spirits (provided by Milo) and the dialogue system (provided by Brad).

## Narrative Role

The narrative role is documented in the GDD, and the cutscenes triggered by completing the final quiz are in the cutscenes.md.

## Advantages

- The staircase puzzle is easy to understand but visually memorable.
- The teleport setup keeps the loop clean.
- The final room has a strong narrative payoff.
- Shared spirit assets make the room easier to author and tune.

