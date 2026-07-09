# WeatherSystem 

## Overview 

The weather system is a blueprint actor that dynamically change the sky of the game by adjusting and lerping through parameters and reacting to events.
And a niagara rain effect that the weather system spawns.

---

## Init Rain 

The custom event that kicks in the weather change. The volumetric clouds StormClouds variable, exponential height fog density, rain system lerps with a timeline to create a dynamic effect simulating real rainy weather. 

## The Listener 

The weather system binds to an delegate
