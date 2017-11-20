/*==============================================================================
 * Mantis Engine image management class headers
 *     Modified: 2017 Nov 20
 *============================================================================*/

#ifndef ME_IMAGE_H
#define ME_IMAGE_H

#include <SDL2/SDL.h>
#include <map>
#include <string>

// forward declarations
class ME_Image;
class ME_ImageBank;

#include "mantis.h"

// imagemap typedef
typedef std::map<std::string, ME_Image*> imagemap_t;

/*==============================================================================
 * ME_Image
 *
 *     An image object is used to hold a single loaded image/texture. This is
 *     a wrapper for SDL textures.
 *============================================================================*/
class ME_Image
{
    public:
        ME_Image(ME_Graphics&, std::string path);
        ~ME_Image();
        SDL_Texture* getTexture();
    private:
        SDL_Texture* _texture;
};

/*==============================================================================
 * ME_ImageBank
 *
 *     A class that stores and manages ME_Image objects. Each image is
 *     associated with a tag that can be used to reference the image.
 *============================================================================*/
class ME_ImageBank
{
    public:
        ME_ImageBank(ME_Graphics&);
        ~ME_ImageBank();

        /*----------------------------------------------------------------------
         * Image insertion functions.                                         */
        void loadImage(std::string path, std::string tag);
        void addImage(ME_Image*, std::string tag);

        /*----------------------------------------------------------------------
         * Image access functions.                                            */
        const ME_Image& getImage(std::string tag) const;

    private:
        ME_Graphics* _context;
        imagemap_t   _images;
};

#endif
