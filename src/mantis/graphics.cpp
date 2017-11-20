/*==============================================================================
 * ME_Graphics implementation
 *     Modified: 2017 Nov 20
 *============================================================================*/

#include "mantis.h"

#include "mantis_exception.h"
#include <SDL2/SDL.h>

ME_Graphics::ME_Graphics(ME_Window& context)
    : _renderer(NULL)
{
    SDL_Window* win = context.getWindow();
	_renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
    if (_renderer == NULL) {
        throw ME_Exception(SDL_GetError());
    }
}

ME_Graphics::~ME_Graphics()
{
    // clear the rendering device
    SDL_DestroyRenderer(_renderer);
    _renderer = NULL;
}

SDL_Renderer* ME_Graphics::getRenderer()
{
    return _renderer;
}
