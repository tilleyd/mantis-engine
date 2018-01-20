/*==============================================================================
 * ME_ImageBank implementation
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

ME_ImageBank::~ME_ImageBank()
{
    // delete the images
    for (imagemap_t::iterator it = _images.begin(); it != _images.end(); ++it) {
		delete it->second;
	}
}

void ME_ImageBank::addImage(ME_Image* img, std::string tag)
{
    _images[tag] = img;
}

ME_Image* ME_ImageBank::getImage(std::string tag)
{
    try {
		return _images.at(tag);
	} catch (...) {
		throw ME_Exception("Error: Invalid stage tag");
	}
}

void ME_ImageBank::allocateImages(ME_Graphics* g)
{
    // allocate all the images
    for (imagemap_t::iterator it = _images.begin(); it != _images.end(); ++it) {
		it->second->allocateImage(g);
	}
}

void ME_ImageBank::deallocateImages()
{
    // deallocate all the images
    for (imagemap_t::iterator it = _images.begin(); it != _images.end(); ++it) {
		it->second->deallocateImage();
	}
}
