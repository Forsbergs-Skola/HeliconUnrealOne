# Interaction System

## Overview

The Interaction System provides a unified way for the player to interact with gameplay objects throughout the project. Instead of implementing unique interaction logic inside the player character for every interactable object, all interactable actors implement a shared interaction interface.

The player only requires a single interaction input (**E**), while every object decides how it should respond when interacted with.

## Purpose

Without a common interaction system, the player Blueprint would require references to every interactable object in the game.

Examples include:

- Radio
- State Switch
- Keypad
- Mailbox
- Tutorial Objects
- Future puzzle objects

Adding a new interactable object would require modifying the player Blueprint every time.

By using an interaction interface, new interactable objects can be added without changing the player character.

## Design Pattern

### Interface Pattern

Every interactable Blueprint implements the same interaction interface.

Rather than checking:

- Is this a Radio?
- Is this a Mailbox?
- Is this a Keypad?

The player simply checks:

> Does this actor implement the Interaction Interface?

If it does, the object's `Interact()` function is executed.

Each Blueprint owns its own interaction logic, making every object self-contained.

## System Flow

1. Player presses **E**.
2. A Line Trace is fired from the player's camera.
3. The first actor hit by the trace is checked for the Interaction Interface.
4. If implemented, `Interact()` is called.
5. The object performs its own behaviour.

Example interactions:

- Radio → Plays dialogue.
- State Switch → Changes room state.
- Keypad → Opens the keypad widget.
- Tutorial Objects → Registers puzzle progress.

## Visual Feedback

Interactable objects can contain a white Point Light.

This provides immediate visual feedback to the player, indicating which objects can currently be interacted with.

The light can also be enabled or disabled dynamically depending on puzzle progression.

## Advantages

- Single interaction input for the entire game.
- Easy to add new interactable objects.
- Player Blueprint remains simple.
- Objects remain independent.
- Highly reusable across different levels.
