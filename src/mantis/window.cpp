/*==============================================================================
 * ME_Window implementation
 *============================================================================*/

#include "mantis.h"

#include "mantis_exception.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <string>
using std::string;

ME_Window::ME_Window(string title, unsigned int width, unsigned int height)
	: _win(NULL)
	, _graphics(NULL)
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
	if (TTF_Init() == -1) {
		throw ME_Exception(TTF_GetError());
	}
	_surf = SDL_GetWindowSurface(_win);
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
	// close SDL extensions
	TTF_Quit();
	IMG_Quit();
}

ME_Graphics* ME_Window::getGraphics()
{
	// lazy initialize the graphics device
	if (_graphics == NULL) {
		_graphics = new ME_Graphics(this);
	}
	return _graphics;
}

SDL_Window* ME_Window::getWindow()
{
	return _win;
}

SDL_Surface* ME_Window::getSurface()
{
	return _surf;
}
