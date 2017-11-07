# Mantis Game Engine
The Mantis Engine is a lightweight game engine written in C++. Mantis
is meant to be compiled with your game and is not a standalone development
environment with a GUI as found in Unity/UE/Godot. It is simply a *library*.

Mantis is built using an *object-oriented* approach to hide the hairy details
of the engine from the game developer. This means that you can easily extend
upon the engine and use the included tools without having to concern yourself
with Mantis' design.

>**Note:** Mantis is still in early development and is therefore unstable.

## Features
* Window management
* Graphics using SDL
* Dynamic & capped FPS control
* Event handling
* Threading

## Future development
* Physics engine
* Sound support
* Maths library
* Data structure library

## Dependencies
* SDL2
* POSIX pthread
