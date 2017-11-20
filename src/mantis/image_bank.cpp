/*==============================================================================
 * ME_ImageBank implementation
 *     Modified: 2017 Nov 20
 *============================================================================*/

#include "mantis_image.h"

#include "mantis.h"
#include "mantis_exception.h"

ME_ImageBank::ME_ImageBank(ME_Graphics* context)
    : _context(context)
    : _images()
{}

ME_ImageBank::~ME_ImageBank()
{
    // delete images
    for (imagemap_t::iterator it = _images.begin(); it != _images.end(); ++it) {
		delete it->second;
	}
}

void ME_ImageBank::loadImage(std::string path, std::string tag)
{
    try {
        ME_Image* newimg = new ME_Image(*_context, path);
        addImage(newimg, tag);
    } catch (...) {
        // TODO more specific exception handling
        throw ME_Exception("Error: could not load image");
    }
}

void ME_ImageBank::addImage(ME_Image* img, std::string tag)
{
    _images[tag] = img;
}

const ME_Image& ME_ImageBank::getImage(std::string tag) const
{
    try {
        ME_Image* img = _images.at(tag);
        return *img;
    } catch (...) {
        throw ME_Exception("Error: Invalid image tag");
    }
}
