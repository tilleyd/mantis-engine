# Mantis Engine
### v0.0.0 (initial release)
The Mantis Engine is a lightweight cross-platform game/graphics engine written
in C++. Mantis is meant to be compiled with your game and is not a standalone
development environment with a GUI as found in Unity/UE/Godot. It should simply
be used as a library.

Mantis is built using an *object-oriented* approach to hide the hairy details
of the engine from the game developer. This means that you can easily extend
upon the engine and use the included tools without having to concern yourself
with Mantis' design.

## Demo
There is an included __Snake__ demo project that you can have a look at if you
want to see how the engine is typically used. To build the demo, download the
repository and use the makefiles (`makefile` for Linux, `makefile-win` for
Windows) to build the demo executable. Note that the demo does not show off all
the features of the engine, merely a small part.

## Features
* Window management
* Dynamic window mode change
* Geometry graphics using SDL2
* Image/texture rendering
* Game loop management
* Event handling
* Threading using pthreads
* Dynamic FPS/VSync changes

## Future development
* Physics engine
* Sound support
* Extended maths library
* Data structure library
* General improvements

## Dependencies
* SDL2
  * SDL2_image
  * SDL2_ttf
* POSIX pthread
