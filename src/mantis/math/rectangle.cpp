/*==============================================================================
 * ME_Rectangle implementation
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

#include "mantis_math.h"

ME_Rectangle::ME_Rectangle(double x, double y, double w, double h) :
    _x(x),
    _y(y),
    _w(w),
    _h(h)
{}

void ME_Rectangle::setX(double x)
{
    _x = x;
}

void ME_Rectangle::setY(double y)
{
    _y = y;
}

void ME_Rectangle::setWidth(double w)
{
    _w = w;
}

void ME_Rectangle::setHeight(double h)
{
    _h = h;
}

double ME_Rectangle::getX() const
{
    return _x;
}

double ME_Rectangle::getY() const
{
    return _y;
}

double ME_Rectangle::getWidth() const
{
    return _w;
}

double ME_Rectangle::getHeight() const
{
    return _h;
}

ME_Rectangle ME_Rectangle::operator+(ME_Vector2D vec)
{
    return ME_Rectangle(_x + vec.getX(), _y + vec.getY(), _w, _h);
}

ME_Rectangle ME_Rectangle::operator-(ME_Vector2D vec)
{
    return ME_Rectangle(_x - vec.getY(), _y - vec.getY(), _w, _h);
}

bool ME_Rectangle::containsPoint(const ME_Vector2D* point) const
{
    return containsPoint(point->getX(), point->getY());
}

bool ME_Rectangle::containsPoint(double x, double y) const
{
    return (x > _x && x < (_x + _w)) &&
            (y > _y && y < (_y + _h));
}

bool ME_Rectangle::collidesWithRectangle(const ME_Rectangle* rect) const
{
    // check for the absence of gaps between edges
    return (_x < rect->getX() + rect->getWidth() &&
            _x + _w > rect->getX() &&
            _y < rect->getY() + rect->getHeight() &&
            _y + _h > rect->getY());
}

bool ME_Rectangle::collidesWithCircle(const ME_Circle* circle) const
{
    return circle->collidesWithRectangle(this);
}

SDL_Rect* ME_Rectangle::getSDLRect()
{
    _rect.x = (int)_x;
    _rect.y = (int)_y;
    _rect.w = (int)_w;
    _rect.h = (int)_h;
    return &_rect;
}
