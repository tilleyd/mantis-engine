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
class ME_Circle;

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
         * Operators.
         * Adds/subtracts the vector to/from the (x, y) point.                */
        ME_Rectangle operator+(ME_Vector2D);
        ME_Rectangle operator-(ME_Vector2D);

        /*----------------------------------------------------------------------
         * Collision check functions                                          */
        bool containsPoint(const ME_Vector2D*) const;
        bool containsPoint(double x, double y) const;
        bool collidesWithRectangle(const ME_Rectangle*) const;
        bool collidesWithCircle(const ME_Circle*) const;

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
         * Operators.                                                         */
        ME_Vector2D& operator+=(const ME_Vector2D&);
        ME_Vector2D& operator-=(const ME_Vector2D&);
        ME_Vector2D& operator*=(double);
        ME_Vector2D& operator/=(double);
        ME_Vector2D operator+(ME_Vector2D);
        ME_Vector2D operator-(ME_Vector2D);

        /*----------------------------------------------------------------------
         * Vector functions.                                                  */
        double getMagnitude() const;
        /* Normalizes the values of the vector to have the same relationship
         * but to have a magnitude of the specified value.                    */
        void normalize(double magnitude = 1.0);
        /* Returns the angle between the two vectors.                         */
        double angleBetween(const ME_Vector2D*) const;
        /* Returns the dot product between the two vectors.                   */
        double dotProduct(const ME_Vector2D*) const;

        /*----------------------------------------------------------------------
         * Angle functions.
         * Returns true if the given object touches the region formed by a
         * cone around the vector with a provided angle.                      */
        bool withinAngle(double angle, const ME_Vector2D*);
        bool withinAngle(double angle, const ME_Rectangle*);
        bool withinAngle(double angle, const ME_Circle*);

    private:
        double _x, _y;
        double _mag;
};

class ME_Circle
{
    public:
        ME_Circle(double x = 0.0, double y = 0.0, double r = 0.0);

        /*----------------------------------------------------------------------
         * Member modifiers and accessors.                                    */
        void setX(double);
        void setY(double);
        void setCenter(double, double);
        void setRadius(double);
        double getX() const;
        double getY() const;
        double getRadius() const;

        /*----------------------------------------------------------------------
         * Collision check functions                                          */
        bool containsPoint(const ME_Vector2D*) const;
        bool containsPoint(double x, double y) const;
        bool collidesWithRectangle(const ME_Rectangle*) const;
        bool collidesWithCircle(const ME_Circle*) const;

    private:
        double _x, _y, _r;

};

#endif
