# Mantis Engine
## ME 0.2.1
The Mantis Engine is a lightweight cross-platform game/graphics engine written
in C++. Mantis is meant to be compiled with your game and is not a standalone
development environment with a GUI as found in Unity/UE/Godot. It should simply
be used as a library.

Mantis is built using an *object-oriented* approach to hide the hairy details
of the engine from the game developer. This means that you can easily extend
upon the engine and use the included tools without having to concern yourself
with Mantis' implementation.

## License
Copyright &copy; 2017 Duncan Tilley <<duncan.tilley@gmail.com>>  
See the [license notice](LICENSE.txt), the [GNU GPL license](COPYING.txt) and
the [GNU LGPL license](COPYING_LESSER.txt) for full details.

## Manual
A detailed wiki page or manual will be released in due time, once the engine
has reached a desired state of functionality.

## Demo
There is an included __Snake__ demo project that you can have a look at if you
want to see how the engine is typically used. To build the demo, download the
repository and use the makefiles (`makefile` for Linux, `makefile-win` for
Windows) to build the demo executable. Note that the demo does not show off all
the features of the engine, merely a small part.

## Features
* Window management
* Entity & stage architecture
* Graphical user interface
* Dynamic window mode change
* Geometry graphics using SDL2
* Image/texture rendering
* Game loop management
* Event handling
* Threading using pthreads
* Dynamic FPS/VSync changes

## Future development

> Development of Mantis has ceased in favour of a 3D accelerated engine.

## Dependencies
* SDL2
  * SDL2_image
  * SDL2_ttf
* POSIX pthread
