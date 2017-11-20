/*==============================================================================
 * ME_Window implementation
 *     Modified: 2017 Nov 20
 *============================================================================*/

#include "mantis.h"

#include "mantis_exception.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
using std::string;

ME_Window::ME_Window(string title, unsigned int width, unsigned int height)
	: _win(NULL)
{
	// create the window
	_win = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
	if (_win == NULL) {
		throw ME_Exception(SDL_GetError());
	}

	// initialize image loading
	// TODO other formats
	int flags = IMG_INIT_PNG;
	if (!(IMG_Init(flags) & flags)) {
		throw ME_Exception(IMG_GetError());
	}
}

ME_Window::~ME_Window()
{
	// destroy the rendering device
	delete _graphics;
	_graphics = NULL;
	// destroy the window
	if (_win) {
		SDL_DestroyWindow(_win);
		_win = NULL;
	}
}

ME_Graphics& ME_Window::getGraphics()
{
	// lazy initialize the graphics device
	if (!_graphics) {
		_graphics = new ME_Graphics(*this);
	}
	return *_graphics;
}

SDL_Window* ME_Window::getWindow()
{
	return _win;
}
