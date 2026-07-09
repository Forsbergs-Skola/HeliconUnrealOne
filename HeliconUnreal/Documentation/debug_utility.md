# DebugUtility

## Overview

`DebugUtility` is a lightweight helper class for runtime debugging in Unreal Engine. It provides a centralized way to display formatted debug messages while ensuring they are automatically removed from shipping builds.

---

## Features

- On-screen debug messages
- Output Log integration
- Compile-time removal in shipping builds
- Type-safe formatting using templates
- Convenience logging macro

---

## SCREEN_LOG

`SCREEN_LOG` is a helper macro that forwards its arguments to `DebugUtility::ScreenMessage()`.

Its main purpose is to reduce typing and improve readability when writing temporary debug output.

In shipping builds, the macro expands to nothing, meaning all calls are removed during compilation and introduce no runtime cost.

---

## ScreenMessage()

`ScreenMessage()` formats a string using Unreal's formatting system before displaying it on screen and writing it to the Output Log.

The function is implemented as a **variadic template**, allowing it to accept any number of formatting arguments while maintaining compile-time type safety. Instead of requiring multiple overloads for different parameter counts, a single function handles every valid combination.

Debug output is only generated in non-shipping builds.

---

## ToLogString()

`ToLogString()` converts values into `FString` so they can be used by Unreal's formatting system.

Common Unreal Engine types such as `FText` and `FName` receive specialized handling, while all other supported types are converted through `LexToString()`. This provides a consistent conversion path regardless of the value being formatted.

The function is implemented as a template, allowing the compiler to generate the appropriate conversion for each type without requiring manual overloads.

---

## Templates

The class makes use of C++ templates for two reasons:

- **Variadic templates** allow `ScreenMessage()` to accept any number of formatting arguments.
- **Function templates** allow `ToLogString()` to convert many different types using a single implementation.

Because template resolution happens at compile time, no runtime type checking is required.

---

## Shipping Builds

Debug logging is intended only for development.

When `UE_BUILD_SHIPPING` is enabled:

- `SCREEN_LOG` expands to nothing.
- `ScreenMessage()` produces no output.

This ensures debugging code has no runtime overhead in release builds.

---

## Design Goals

`DebugUtility` is designed to provide:

- A single location for debug logging utilities.
- Minimal boilerplate when writing debug messages.
- Consistent formatting across the project.
- Zero-cost removal of debug output in shipping builds.
- Simple integration into gameplay and engine code.