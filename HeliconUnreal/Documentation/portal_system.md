# Portal System Documentation

## Overview

This document covers the current portal system, which is the v2 version used in `HeliconUnreal`.

The portal setup is used to move the player through space while keeping the experience feeling continuous and connected. It supports the project's seamless one-map structure rather than behaving like a one-off level script.

## Purpose

The portal system exists to create smooth traversal and to support the game's larger sense of spatial continuity.

It is especially useful for:

- Moving the player between spaces without a hard loading moment.
- Building the illusion of one connected world.
- Keeping transitions visually controlled.
- Reusing the same portal logic across different scenes.

## Current Version

The current implementation lives in the `Content/PortalSystem` content set and is centered around:

- `Portal_BP`
- `Portal_MAT`
- `PortalMesh`
- `BP_CutscenePortalManager`
- `PortalLevel.umap`

This version is the one implemented in `HeliconUnreal`.

<img width="628" height="711" alt="image" src="https://github.com/user-attachments/assets/76bc9635-69a7-4fdc-a5d6-240f754c77bc" />


## Version 1 Notes

v1 was the original portal prototype TestPortal. It focused on a simple walk-through portal that could show the destination space through a live render target, then move the player through the portal with overlap-driven teleport logic.

### V1 Placeholder Notes

- Visual style: a flat portal surface built from `BP_Portal`, `M_Portal`, and `M_Portal_B`, with portal views driven by `RT_PortalViewA` and `RT_PortalViewB`.
- Player interaction: the player entered by overlapping the portal trigger, and `BP_Portal` handled the overlap, portal collision, and teleport checks.
- Transition behaviour: the blueprint updated a scene capture view, applied a clip plane, and used `TryTeleport` and `ResetTeleport` to keep the transition seamless.
- Limitations: the setup was tightly coupled to one blueprint and a fixed render-target pair, which made it less flexible for scaling across more spaces. It also visually looked flat and a lot worse than the new version.
- Reason for replacement: v2 separated the portal sequence into a cleaner reusable system so the transition could be managed, staged, and reused more easily. It also looked a lot smoother

## Version 2 Goals

The second version is the version used in the current `HeliconUnreal` project.

It is built around the actual portal content in `Content/PortalSystem` and is designed to support the game's seamless one-map structure. The player can move between areas without feeling like the world has been split into separate levels.

This version also supports the bigger idea behind the game's level design. The portals help the house, basement, and other spaces feel like they belong to one connected world, while still letting each area be authored independently.

## How The System Works

The current setup is made from a small set of project assets that each handle a different part of the experience:

- `Portal_BP` is the main portal actor.
- `Portal_MAT` handles the visual portal surface.
- `PortalMesh` provides the portal geometry.
- `BP_CutscenePortalManager` can coordinate portal-driven transitions when a sequence needs to be staged.
- `PortalLevel.umap` is the authored portal space used for the system.

This makes the portal setup easier to understand as a complete system instead of a single teleport Blueprint.

The portal is meant to support seamless traversal through `Map_Game`, which matches the level design approach used elsewhere in the project. The player experiences the world as one connected space, even when the portal is moving them between different areas.

## Why V2 Exists

Compared to the earlier prototype, v2 is cleaner, more reusable, and easier to document.

The older portal version was more tightly tied to a specific render-target and overlap-based setup. The current system is more clearly organized around the project content itself, which makes it better suited to the way `HeliconUnreal` is built.

## Project Use

In `HeliconUnreal`, portals are part of the game's broader traversal and level design structure.

They are used to:

- Move the player between spaces without breaking immersion.
- Support the illusion of one connected world.
- Keep portal visuals and portal logic separate.
- Give the team a reusable portal setup for the rest of the project.

This section should stay focused on the actual `HeliconUnreal` portal implementation rather than the older prototype language.

## Advantages

- Reusable across multiple levels or spaces.
- Easier to maintain than a one-off teleport setup.
- Supports a more polished traversal experience.
- Offers a unique approach to level design and storytelling.


## Improvements

- Remove the tiny stutter that happens when you cross the portal. It's slightly managed by the 'PortalOffset' variable in the BP
- Make it less laggy. The render targets are very intensive, which is why they turn off when player isn't close, but they still cause frame drops when active
- Allow physics objects to move through them. Could create some interesting puzzle opportunities.
