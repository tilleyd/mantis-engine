/*==============================================================================
 * Mantis Engine math class headers
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

#ifndef ME_MATH_H
#define ME_MATH_H

#include <SDL2/SDL.h>

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
