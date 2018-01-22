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

// forward declarations
class ME_Rectangle;
class ME_Vector2D;

#include <SDL2/SDL.h>

/*==============================================================================
 * ME_Rectangle
 *
 *     A basic rectangular object that has a position, width and height.
 *============================================================================*/
class ME_Rectangle
{
    public:
        ME_Rectangle(double x = 0.0, double y = 0.0,
                double w = 0.0, double h = 0.0);

        /*----------------------------------------------------------------------
         * Member modify functions                                            */
        void setX(double);
        void setY(double);
        void setWidth(double);
        void setHeight(double);

        /*----------------------------------------------------------------------
         * Member access functions                                            */
        double getX() const;
        double getY() const;
        double getWidth() const;
        double getHeight() const;

        /*----------------------------------------------------------------------
         * Collision check functions                                          */
        bool containsPoint(ME_Vector2D*) const;
        bool containsPoint(double x, double y) const;
        bool collidesWithRectangle(const ME_Rectangle*) const;

        /*----------------------------------------------------------------------
         * Returns an SDL rectangle with truncated integer values.            */
        SDL_Rect* getSDLRect();

    private:
        double _x, _y, _w, _h;
        SDL_Rect _rect;
};

class ME_Vector2D
{
    public:
        ME_Vector2D(double x = 0.0, double y = 0.0);

        /*----------------------------------------------------------------------
         * Member modifiers and accessors.                                    */
        void setX(double);
        void setY(double);
        void setValue(double, double);
        double getX() const;
        double getY() const;

        /*----------------------------------------------------------------------
         * Magnitude functions.                                               */
        double getMagnitude() const;
        /* Normalizes the values of the vector to have the same relationship
         * but to have a magnitude of the specified value.                    */
        void normalize(double magnitude = 1.0);

    private:
        double _x, _y;
        double _mag;
};

#endif
