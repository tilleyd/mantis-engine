/*==============================================================================
 * ME_Image implementation
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

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
using std::string;

ME_Image::ME_Image(ME_Graphics* graphics, string path)
    : _texture(NULL)
{
    // create the SDL surface
    SDL_Surface* surface = IMG_Load(path.c_str());
    if (surface == NULL) {
        throw ME_Exception(IMG_GetError());
    }
    // create hardware accelerated texture from the surface
    _texture = SDL_CreateTextureFromSurface(graphics->getSDLRenderer(),
            surface);
    SDL_FreeSurface(surface);
    if (_texture == NULL) {
        throw ME_Exception(SDL_GetError());
    }
    // set the alpha blending mode
    SDL_SetTextureBlendMode(_texture, SDL_BLENDMODE_BLEND);
    // get width and height
    SDL_QueryTexture(_texture, NULL, NULL, &_width, &_height);
}

ME_Image::~ME_Image()
{
    // free the loaded texture
    SDL_DestroyTexture(_texture);
    _texture = NULL;
}

int ME_Image::getWidth() const
{
    return _width;
}

int ME_Image::getHeight() const
{
    return _height;
}

void ME_Image::setAlpha(int a)
{
    SDL_SetTextureAlphaMod(_texture, a);
}

void ME_Image::draw(ME_Graphics* g)
{
    // render the entire screen with the image
    int r = SDL_RenderCopy(g->getSDLRenderer(), _texture, NULL, NULL);
    if (r) {
        throw (ME_Exception(SDL_GetError()));
    }
}

void ME_Image::draw(ME_Graphics* g, ME_Rectangle* rect)
{
    // render at the given position with stretching
    SDL_Rect* dest = rect->getSDLRect();
    int r = SDL_RenderCopy(g->getSDLRenderer(), _texture, NULL, dest);
    if (r) {
        throw (ME_Exception(SDL_GetError()));
    }
}
