# Keypad Puzzle

## Overview

The Keypad Puzzle serves as the final interaction in the switchpuzzle room.

The player must discover the correct code before progression is possible.

## Purpose

The keypad combines environmental exploration with player interaction.

Rather than presenting the solution directly, the player must gather information from the environment before entering the correct code.

## System Flow

1. The player interacts with the keypad.
2. The Keypad Widget opens.
3. Player movement is temporarily disabled.
4. The player enters a code.
5. The entered code is validated.

If the code is incorrect:

- The input is cleared.
- The player may try again.

If the code is correct:

- The puzzle is marked as completed.
- The keypad becomes non-interactable.
- Progression events are triggered.

## Advantages

- Combines UI with gameplay.
- Prevents accidental player movement while entering a code.
- Supports repeated attempts.
- Clearly communicates puzzle completion.
