/*==============================================================================
 * ME_Image implementation
 *============================================================================*/

#include "mantis_image.h"

#include "mantis.h"
#include "mantis_exception.h"
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

SDL_Texture* ME_Image::getTexture()
{
    return _texture;
}
