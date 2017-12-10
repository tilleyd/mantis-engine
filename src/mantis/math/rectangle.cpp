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

ME_Rectangle::ME_Rectangle(int x, int y, int w, int h)
    : _x(x)
    , _y(y)
    , _w(w)
    , _h(h)
{}

void ME_Rectangle::setX(int x)
{
    _x = x;
}

void ME_Rectangle::setY(int y)
{
    _y = y;
}

void ME_Rectangle::setWidth(int w)
{
    _w = w;
}

void ME_Rectangle::setHeight(int h)
{
    _h = h;
}

int ME_Rectangle::getX() const
{
    return _x;
}

int ME_Rectangle::getY() const
{
    return _y;
}

int ME_Rectangle::getWidth() const
{
    return _w;
}

int ME_Rectangle::getHeight() const
{
    return _h;
}

bool ME_Rectangle::containsPoint(int x, int y) const
{
    return (x > _x && x < (_x + _w)) && (y > _y && y < (_y + _h));
}

bool ME_Rectangle::collidesWithRectangle(const ME_Rectangle* rect) const
{
    // check for the absence of gaps between edges
    return (_x < rect->_x + rect->_w && _x + _w > rect->_x &&
            _y < rect->_y + rect->_h && _y + _h > rect->_y);
}

SDL_Rect ME_Rectangle::getSDLRect() const
{
    SDL_Rect rect;
    rect.x = _x;
    rect.y = _y;
    rect.w = _w;
    rect.h = _h;
    return rect;
}
