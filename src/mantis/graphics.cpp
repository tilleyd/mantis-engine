/*==============================================================================
 * ME_Graphics implementation
 *============================================================================*/

#include "mantis.h"

#include "mantis_exception.h"
#include "mantis_image.h"
#include <SDL2/SDL.h>

ME_Graphics::ME_Graphics(ME_Window* context)
    : _renderer(NULL)
{
    SDL_Window* win = context->getWindow();
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

void ME_Graphics::clear()
{
    SDL_RenderClear(_renderer);
}

void ME_Graphics::drawImage(ME_Image* img)
{
    SDL_RenderCopy(_renderer, img->getTexture(), NULL, NULL);
}

void ME_Graphics::drawImage(ME_Image* img, int x, int y)
{
    drawImage(img, x, y, img->getWidth(), img->getHeight());
}

void ME_Graphics::drawImage(ME_Image* img, int x, int y, int w, int h)
{
    SDL_Rect dest;
    dest.x = x;
    dest.y = y;
    dest.w = w;
    dest.h = h;
    // render at the given position with stretching
    SDL_RenderCopy(_renderer, img->getTexture(), NULL, &dest);
}

void ME_Graphics::setColor(int a, int r, int g, int b)
{
    SDL_SetRenderDrawColor(_renderer, r, g, b, a);
}

SDL_Renderer* ME_Graphics::getRenderer()
{
    return _renderer;
}
