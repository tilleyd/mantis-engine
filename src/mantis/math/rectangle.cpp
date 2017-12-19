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
{
    _rect.x = x;
    _rect.y = y;
    _rect.w = w;
    _rect.h = h;
}

void ME_Rectangle::setX(int x)
{
    _rect.x = x;
}

void ME_Rectangle::setY(int y)
{
    _rect.y = y;
}

void ME_Rectangle::setWidth(int w)
{
    _rect.w = w;
}

void ME_Rectangle::setHeight(int h)
{
    _rect.h = h;
}

int ME_Rectangle::getX() const
{
    return _rect.x;
}

int ME_Rectangle::getY() const
{
    return _rect.y;
}

int ME_Rectangle::getWidth() const
{
    return _rect.w;
}

int ME_Rectangle::getHeight() const
{
    return _rect.h;
}

bool ME_Rectangle::containsPoint(int x, int y) const
{
    return (x > _rect.x && x < (_rect.x + _rect.w)) &&
            (y > _rect.y && y < (_rect.y + _rect.h));
}

bool ME_Rectangle::collidesWithRectangle(const ME_Rectangle* rect) const
{
    // check for the absence of gaps between edges
    return (_rect.x < rect->getX() + rect->getWidth() &&
            _rect.x + _rect.w > rect->getX() &&
            _rect.y < rect->getY() + rect->getHeight() &&
            _rect.y + _rect.h > rect->getY());
}

SDL_Rect* ME_Rectangle::getSDLRect()
{
    return &_rect;
}
