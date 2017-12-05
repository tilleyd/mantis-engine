/*==============================================================================
 * Mantis Engine math class headers
 *============================================================================*/

#ifndef ME_MATH_H
#define ME_MATH_H

#include <SDL2/SDL.h>

// forward declarations
class ME_Rectangle;

/*==============================================================================
 * ME_Rectangle
 *
 *     A basic rectangular object that has a position, width and height.
 *============================================================================*/
class ME_Rectangle
{
    public:
        ME_Rectangle(int x, int y, int w, int h);

        /*----------------------------------------------------------------------
         * Member modify functions                                            */
        void setX(int);
        void setY(int);
        void setWidth(int);
        void setHeight(int);

        /*----------------------------------------------------------------------
         * Member access functions                                            */
        int getX() const;
        int getY() const;
        int getWidth() const;
        int getHeight() const;

        /*----------------------------------------------------------------------
         * Collision check functions                                          */
        bool containsPoint(int x, int y) const;
        bool collidesWithRectangle(const ME_Rectangle*) const;

        SDL_Rect getSDLRect() const;

    private:
        int _x;
        int _y;
        int _w;
        int _h;
};

#endif
