/*==============================================================================
 * Mantis Engine image management class headers
 *     Modified: 2017 Nov 20
 *============================================================================*/

#ifndef ME_IMAGE_H
#define ME_IMAGE_H

#include <SDL2/SDL_image.h>
#include <map>
#include <string>

// forward declarations
class ME_Image;
class ME_ImageBank;

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
        ME_Image(std::string path);
        ~ME_Image();
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
        ME_ImageBank();
        ~ME_ImageBank();

        /*----------------------------------------------------------------------
         * Image insertion functions.                                         */
        void loadImage(std::string path, std::string tag);
        void addImage(ME_Image*, std::string tag);

        /*----------------------------------------------------------------------
         * Image access functions.                                            */
        const ME_Image& getImage(std::string tag) const;

    private:
        imagemap_t _images;
};

#endif
