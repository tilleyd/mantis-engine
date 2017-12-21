/*==============================================================================
 * ME_Graphics implementation
 *==============================================================================
 * Copyright (C) 2017 Duncan Tilley <duncan.tilley@gmail.com>
 *
 * This file is part of Mantis Engine.
 *
 * Mantis Engine is free software: you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or (at your
 * option) any later version.
 *
 * Mantis Engine is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more
 * details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with Mantis Engine.  If not, see <http://www.gnu.org/licenses/>.
 *============================================================================*/

#include "mantis.h"

#include "mantis_exception.h"
#include "mantis_image.h"
#include "math/mantis_math.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
using std::string;

ME_Graphics::ME_Graphics(ME_Window* context):
    _renderer(NULL),
    _color(NULL),
    _font(NULL),
    _smoothfont(false),
    _texturefilt(false)
{
    SDL_Window* win = context->getSDLWindow();
	_renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
    if (_renderer == NULL) {
        throw ME_Exception(SDL_GetError());
    }
    // set the alpha blending mode
    SDL_SetRenderDrawBlendMode(_renderer, SDL_BLENDMODE_BLEND);
    _color = new SDL_Color;
    _color->r = 255;
    _color->g = 255;
    _color->b = 255;
    _color->a = 255;
}

ME_Graphics::~ME_Graphics()
{
    // clear the members
    SDL_DestroyRenderer(_renderer);
    delete _color;
    TTF_CloseFont(_font);
    _renderer = NULL;
    _color = NULL;
    _font = NULL;
}

void ME_Graphics::clear()
{
    SDL_RenderClear(_renderer);
}

void ME_Graphics::setColor(int r, int g, int b)
{
    setColor(255, r, g, b);
}

void ME_Graphics::setColor(int a, int r, int g, int b)
{
    _color->a = a;
    _color->r = r;
    _color->g = g;
    _color->b = b;
    SDL_SetRenderDrawColor(_renderer, r, g, b, a);
}

void ME_Graphics::setTextureFiltering(bool f)
{
    // enable or disable linear texture filtering
    // anisotropic is not supported since it is only available with Direct3D
    if (f != _texturefilt) {
        if (f) {
            SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
        } else {
            SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0");
        }
    }
}

void ME_Graphics::setSmoothFonts(bool s)
{
    _smoothfont = s;
}

void ME_Graphics::drawImage(ME_Image* img)
{
    img->draw(this);
}

void ME_Graphics::drawImage(ME_Image* img, int x, int y)
{
    drawImage(img, x, y, img->getWidth(), img->getHeight());
}

void ME_Graphics::drawImage(ME_Image* img, int x, int y, int w, int h)
{
    ME_Rectangle dest(x, y, w, h);
    img->draw(this, &dest);
}

void ME_Graphics::drawRect(const ME_Rectangle* rect)
{
    drawRect(rect->getX(), rect->getY(), rect->getWidth(), rect->getHeight());
}

void ME_Graphics::drawRect(int x, int y, int w, int h)
{
    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = w;
    rect.h = h;
    SDL_RenderDrawRect(_renderer, &rect);
}

void ME_Graphics::fillRect(const ME_Rectangle* rect)
{
    fillRect(rect->getX(), rect->getY(), rect->getWidth(), rect->getHeight());
}

void ME_Graphics::fillRect(int x, int y, int w, int h)
{
    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = w;
    rect.h = h;
    SDL_RenderFillRect(_renderer, &rect);
}

void ME_Graphics::drawLine(int x1, int y1, int x2, int y2)
{
    SDL_RenderDrawLine(_renderer, x1, y1, x2, y2);
}

void ME_Graphics::drawText(int x, int y, string text)
{
    drawText(x, y, text, NULL);
}

void ME_Graphics::drawText(int x, int y, string text, ME_Rectangle* clip)
{
    if (!_font) {
        throw ME_Exception("No font set for drawing text");
    }
    // create the text surface
    SDL_Surface* surface = NULL;
    if (_smoothfont) {
        surface = TTF_RenderText_Blended(_font, text.c_str(), *_color);
    } else {
        surface = TTF_RenderText_Solid(_font, text.c_str(), *_color);
    }
    if (surface) {
        // create the text texture
        SDL_Texture* texture = NULL;
        texture = SDL_CreateTextureFromSurface(_renderer, surface);
        if (texture) {
            SDL_Rect dest;
            dest.x = x;
            dest.y = y;
            dest.w = surface->w;
            dest.h = surface->h;
            SDL_Rect* clipping = NULL;
            if (clip) {
                clipping = clip->getSDLRect();
                // make sure the clipped text does not stretch
                dest.w = dest.w < clipping->w ? dest.w : clipping->w;
                dest.h = dest.h < clipping->h ? dest.h : clipping->h;
            }
            SDL_RenderCopy(_renderer, texture, clipping, &dest);
            SDL_DestroyTexture(texture);
        }
        SDL_FreeSurface(surface);
    }
}

int ME_Graphics::getTextHeight(string text)
{
    int h;
    if (!_font) {
        throw ME_Exception("No font set for drawing text");
    }
    if (!TTF_SizeText(_font, text.c_str(), NULL, &h)) {
        return h;
    } else {
        throw ME_Exception(TTF_GetError());
    }
}

int ME_Graphics::getTextWidth(string text)
{
    int w;
    if (!_font) {
        throw ME_Exception("No font set for drawing text");
    }
    if (!TTF_SizeText(_font, text.c_str(), &w, NULL)) {
        return w;
    } else {
        throw ME_Exception(TTF_GetError());
    }
}

void ME_Graphics::setFont(string fname, int size)
{
    _font = TTF_OpenFont(fname.c_str(), size);
    if (!_font) {
        throw ME_Exception(TTF_GetError());
    }
}

SDL_Renderer* ME_Graphics::getSDLRenderer()
{
    return _renderer;
}

void ME_Graphics::recreateSDLRenderer(ME_Window* context, bool vsync)
{
    SDL_DestroyRenderer(_renderer);
    SDL_Window* win = context->getSDLWindow();
    int flags = SDL_RENDERER_ACCELERATED;
    if (vsync) {
        flags |= SDL_RENDERER_PRESENTVSYNC;
    }
	_renderer = SDL_CreateRenderer(win, -1, flags);
    if (_renderer == NULL) {
        throw ME_Exception(SDL_GetError());
    }
    // set the alpha blending mode
    SDL_SetRenderDrawBlendMode(_renderer, SDL_BLENDMODE_BLEND);
}
