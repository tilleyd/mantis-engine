/*==============================================================================
 * ME_Window implementation
 *     Author  : Duncan Tilley
 *     Modified: 2017 Oct 30
 *============================================================================*/

 #include "mantis.h"

 #include <SDL2/SDL.h>

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
}

ME_Window::~ME_Window()
{
	// destroy the window
	if (_win) {
		SDL_DestroyWindow(_win);
		_win = NULL;
	}
}
