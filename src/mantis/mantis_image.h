/*==============================================================================
 * Mantis Engine image management class headers
 *============================================================================*/

#ifndef ME_IMAGE_H
#define ME_IMAGE_H

#include <SDL2/SDL.h>
#include <string>
#include <vector>

// forward declarations
class ME_Image;
class ME_ImageSheet;

#include "mantis.h"
#include "math/mantis_math.h"

// rectlist typedef
typedef std::vector<SDL_Rect*> rectlist_t;

/*==============================================================================
 * ME_Image
 *
 *     An image object is used to hold a single loaded image/texture. This is
 *     basically a wrapper class for SDL textures.
 *============================================================================*/
class ME_Image
{
    public:
        ME_Image(ME_Graphics*, std::string path);
        virtual ~ME_Image();

        virtual int getWidth() const;
        virtual int getHeight() const;

        /*----------------------------------------------------------------------
         * Rendering functions (though it is better to use
         * ME_Graphics::drawImage, which makes us of these functions)         */
        virtual void draw(ME_Graphics*);
        virtual void draw(ME_Graphics*, ME_Rectangle*);
    protected:
        SDL_Texture* _texture;
        int          _width;
        int          _height;
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
        ME_ImageSheet(ME_Graphics*, std::string path, int startx, int starty,
                int imgw, int imgh, int rows, int cols, int numimgs);
        virtual ~ME_ImageSheet();

        virtual int getWidth() const;
        virtual int getHeight() const;

        /*----------------------------------------------------------------------
         * Rendering functions (though it is better to use
         * ME_Graphics::drawImage, which makes us of these functions)         */
        virtual void draw(ME_Graphics*);
        virtual void draw(ME_Graphics*, ME_Rectangle*);

        /*----------------------------------------------------------------------
         * Image selection function. The images are numbered from 0 in row
         * major form.                                                        */
        void setCurrentImage(unsigned int);

        /*----------------------------------------------------------------------
         * Animation functions.                                               */
        void setAnimationFrequency(double fps);
        void updateCurrentImage(double period);

    private:
        rectlist_t    _bounds;
        int           _iwidth;
        int           _iheight;
        double        _frequency;
        int           _current;
        double        _time;
};

#endif
