/*==============================================================================
 * Mantis Engine image management class headers
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

#ifndef ME_IMAGE_H
#define ME_IMAGE_H

#include <SDL2/SDL.h>
#include <map>
#include <string>
#include <vector>

#define IMG_RANGE_ALL -1

// animation range struct
struct animrange_t
{
    int start;
    int end;
};

// datastruct typedefs
typedef std::vector<SDL_Rect*> rectlist_t;
typedef std::vector<animrange_t> rangelist_t;
typedef std::map<std::string, ME_Image*> imagemap_t;

/*==============================================================================
 * ME_Image
 *
 *     An image object is used to hold a single loaded image/texture. This is
 *     basically a wrapper class for SDL textures.
 *============================================================================*/
class ME_Image
{
    public:
        /*----------------------------------------------------------------------
         * Note that the constructor does not load the image. The image is only
         * loaded after a call to allocateImage().                            */
        ME_Image(std::string path);
        virtual ~ME_Image();

        /*----------------------------------------------------------------------
         * Image bound accessors. These are only valid after allocating the
         * image.                                                             */
        virtual int getWidth() const;
        virtual int getHeight() const;

        virtual void setAlpha(int);

        /*----------------------------------------------------------------------
         * Remove the image from memory or reload it, to be used in the
         * stage's allocateResources() and deallocateResources() functions.   */
        virtual void allocateImage(ME_Graphics*);
        virtual void deallocateImage();

        /*----------------------------------------------------------------------
         * Rendering functions (though it is better to use
         * ME_Graphics::drawImage, which makes us of these functions)         */
        virtual void draw(ME_Graphics*);
        virtual void draw(ME_Graphics*, ME_Rectangle*);
    protected:
        SDL_Texture* _texture;
        int          _width;
        int          _height;
        std::string  _path;
};

/*==============================================================================
 * ME_ImageSheet
 *
 *     An image object that splits the renderable image into individual images
 *     that can be rendered separately. This is used to logically group images
 *     or for use as an animation.
 *============================================================================*/
class ME_ImageSheet : public ME_Image
{
    public:
        /*----------------------------------------------------------------------
         * The constructor splits the images starting at the start point in a
         * matrix form for the number of rows and columns. The imgw and imgh is
         * the size of each individual image.                                 */
        ME_ImageSheet(std::string path, int startx, int starty, int imgw,
                int imgh, int rows, int cols, int numimgs);
        /* This constructor assumes that the entire sheet is a row of images. */
        ME_ImageSheet(std::string path, int imgw, int imgh, int numimgs);
        virtual ~ME_ImageSheet();

        virtual int getWidth() const;
        virtual int getHeight() const;
        virtual int getNumImages() const;

        /*----------------------------------------------------------------------
         * Rendering functions (though it is better to use
         * ME_Graphics::drawImage, which makes use of these functions).       */
        virtual void draw(ME_Graphics*);
        virtual void draw(ME_Graphics*, ME_Rectangle*);

        /*----------------------------------------------------------------------
         * Image selection function. The images are numbered from 0 in row
         * major form.                                                        */
        void setCurrentFrame(int);

    private:
        // frame rectangle bounds
        rectlist_t    _bounds;

        // sheet variables
        unsigned int  _iwidth;
        unsigned int  _iheight;
        unsigned int  _curFrame;
};

/*==============================================================================
 * ME_Animation
 *
 *     Uses an image sheet as an animation, allowing you to select and use
 *     certain ranges of frames as animations. Note that the animation does
 *     not take ownership of the image (i.e. it is not freed on deletion).
 *============================================================================*/
class ME_Animation
{
    public:
        ME_Animation(ME_ImageSheet*);

        /*----------------------------------------------------------------------
         * Animation functions.                                               */
        void setCurrentFrame(int);
        void setAnimationDuration(double sec);
        void updateAnimation(double period);
        /* These let you to use only a subset of images for animations, allowing
         * multiple animations from a single sheet. Added ranges are indexed
         * from 0, and IMG_RANGE_ALL for all frames/images.                   */
        void addAnimationRange(int start, int end);
        void setAnimationRange(int index);

        ME_Image* getImage();
    private:
        ME_ImageSheet* _sheet;

        // animation range variables
        rangelist_t _ranges;
        int         _curRange;
        int         _rangeLength;
        int         _rangeStart;

        // animation update variables
        double      _duration;
        double      _time;
        int         _curFrame;
};

/*==============================================================================
 * ME_ImageBank
 *
 *     A collection of images that can be loaded or unloaded in bulk. Each image
 *     is associated with a tag for easy access.
 *============================================================================*/
class ME_ImageBank
{
    public:
        ~ME_ImageBank();

        /*----------------------------------------------------------------------
         * Image management functions.                                        */
        void addImage(ME_Image*, std::string tag);
        ME_Image* getImage(std::string tag);

        void allocateImages(ME_Graphics*);
        void deallocateImages();
    private:
        imagemap_t _images;
};

#endif
