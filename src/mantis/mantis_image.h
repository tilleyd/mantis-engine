/*==============================================================================
 * Mantis Engine image management class headers
 *     Author  : Duncan Tilley
 *     Modified: 2017 Nov 18
 *============================================================================*/

#ifndef ME_IMAGE_H
#define ME_IMAGE_H

#include <string>
#include <SDL2/SDL_image.h>

// forward declarations
class ME_Image;
class ME_ImageBank;

/*==============================================================================
 * ME_Image
 *
 *     An image object is used to hold a single loaded image/texture. This is
 *     a wrapper for SDL textures.
 *============================================================================*/
class ME_Image
{
    public:
        // TODO
};

/*==============================================================================
 * ME_ImageBank
 *
 *     A singleton class that stores and manages ME_Image objects. Each image
 *     is associated with a tag that can be used to reference the image. The
 *     image bank is therefore a kind of image map/dictionary.
 *============================================================================*/
class ME_ImageBank
{
    public:
        // TODO
};

#endif
