# Ending Cutscenes Documentation

## Overview

The project has two ending cutscenes: `goodending` and `badending`.

Both sequences are used to close out the game and move the player into the credits presentation.

## Purpose

The ending cutscenes provide narrative payoff and a clear transition out of gameplay.

They also let the final mood of the game land properly before the credits begin.

## Cutscene Setup

The ending content is split into two outcomes:

- Good ending
- Bad ending

The project can decide which ending to play based on the current game state, including the ending state stored in the game instance. Details of the cutscenes aesthetics can be found in the GDD.

## Assets Involved

Relevant content includes:

- `GoodEnding`
- `BadEnding`
- `WBP_GoodCredits`
- `WBP_BadCredits`
- `BP_Credits`
- `BP_CreditsActor`

The cutscene asset and the credits widget work together as the final presentation layer.

## Flow

1. The game reaches the ending state.
2. The correct cutscene is selected.
3. The ending sequence plays.
4. The corresponding credits widget is shown.
5. The credits roll or remain visible as the final output of the game.

## Credits Widget

The credits presentation is handled through widget content and is loaded on a separate map.

There are two different widgets, each matching the ending of the cutscene, with the GoodCredits being visually brighter and the BadCredits being visually darker. The functionality is the same.

## Advantages

- Gives the game a clear narrative finish.
- Keeps cutscene logic and UI logic separated.
- Makes it easy to swap or extend the final presentation later.

## Improvements

- Longer cutscenes with more detailed animation. I used this project as an introduction to UE5s cinematic creation possibilities
- Use the same widget and tweak the colour/properties with BPs. Seems like better practice.

