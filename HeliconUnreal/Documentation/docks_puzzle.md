# Docks Puzzle Documentation

## Overview

The Docks Puzzle is a turn based puzzle that involves multiple actors and requires the player to light up 3 buoys, without a seagull turning them off

The player uses a spotlight to activate dock lights, while gulls react to the puzzle state and move between targets. The system is designed so that each actor has a single job, which keeps the puzzle easy to expand or rebalance.

## Purpose

The docks section combines environmental storytelling with a more active puzzle loop.

The gulls will always move to the first light that they see turn on, stopping to rest on a rock/rest point if it is in the wat. The player can distract the gulls but illuminating the "decoy" light, which the gulls will always prioritise flying to.

It gives the player a clear interaction target, but it also introduces moving puzzle pieces that create pressure and timing:

- The player controls the spotlight.
- Buoys and decoy lights provide puzzle targets.
- Gulls react to which lights are active.
- Rest points affect gull movement and routing.


## Architecture

The puzzle is split into several actors:

| Class | Responsibility |
| --- | --- |
| `ADocksPuzzleManager` | Owns the puzzle flow, turn order, win condition, and actor registration. |
| `ASpotlightActor` | Lets the player trace and hold on a target light. |
| `AADockLightTemplate` | Base class for dock lights, including buoys and decoys. |
| `AGullActor` | Handles gull movement, target selection, and turn progression. |
| `AGullRestPoint` | Provides blocking volumes that can interrupt gull movement. |

## Puzzle Flow

1. `ADocksPuzzleManager` gathers all puzzle actors at the start of play.
2. The puzzle enters the player turn.
3. The player uses `ASpotlightActor` to trace an unlit dock light.
4. If the beam is held long enough, the light is activated.
5. Activated lights receive an activation order through the manager.
6. The player ends their turn.
7. The gull turn begins and each `AGullActor` chooses a target based on the current puzzle state.
8. Gulls move toward their targets, react to rest points, and complete their individual steps.
9. The manager checks the win condition.
10. If all required lights are active, the puzzle is completed.

## Light System

`AADockLightTemplate` is the shared base for all dock lights.

Relevant properties:

- `bIsLit` tracks whether the light is active.
- `bRequiredForWin` marks the light as part of the solution.
- `bIsDecoy` marks a light as bait rather than a required solution piece.
- `ActivationOrder` stores the order in which lights were activated.

This allows the puzzle to support both required targets and fake-out targets without needing separate systems.

## Spotlight Interaction

`ASpotlightActor` is the player-facing interaction layer for the puzzle.

It uses a trace to find an unlit target, then keeps track of contact time until the light can be switched on.

Relevant settings:

- `RequiredHoldTime` controls how long the player must hold on a target.
- `TraceDistance` controls how far the spotlight can reach.
- `TraceChannel` controls what the trace can hit.
- `bDrawDebugTrace` can be enabled while testing the puzzle.

The spotlight is also reset through the puzzle manager, which keeps the puzzle state consistent between attempts.

It rotates through BPs to visually help the player.

## Gull Behaviour

`AGullActor` provides the movement and state logic for each gull in the puzzle.

The gull can move between states such as:

- `Idle`
- `MovingToTarget`
- `WaitingAtRestPoint`
- `Swarming`

Each gull can:

- Choose a target light.
- Move through the environment in a controlled way.
- Pause when blocked by a rest point.
- Notify the puzzle manager when its turn step is complete.

This gives the puzzle a sense of progression and makes the gulls feel like part of the environment rather than static decorations.

They have a very simple flying animation and model in BPs to help achieve this.

## Rest Points/Rocks

`AGullRestPoint` creates blocking zones that affect gull movement, forcing them to spend a turn on the rest point.

The rest points help shape the gull routes and can be used to create more readable or more difficult flight patterns.

The `BlockingRadius` property makes it easy to tune how much space each rest point occupies in the puzzle.

## Blueprint Hooks

The manager exposes Blueprint events for the major puzzle beats:

- `BP_PlayerTurnStarted`
- `BP_GullTurnStarted`
- `BP_PuzzleCompleted`

These events let level scripts, audio, VFX, or UI react to the puzzle without hard-coding extra references into the C++ layer.

## Advantages

- The puzzle is modular and easy to author in the editor.
- Player input and creature behaviour stay cleanly separated.
- Lights, gulls, and rest points can all be tuned independently.
- The manager keeps the puzzle state in one place.
- Blueprint events make it easy to extend the sequence with presentation logic.

## Improvements

- More visually clear assets for the decoy and rock
- A puzzle layout that is clearer for the player to understand
- Better seagull flight animation
- Visual light beam from the spotlight

