/*==============================================================================
 * ME_Circle implementation
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

ME_Circle::ME_Circle(double x, double y, double r) :
    _x(x),
    _y(y),
    _r(r)
{}

void ME_Circle::setX(double x)
{
    _x = x;
}

void ME_Circle::setY(double y)
{
    _y = y;
}

void ME_Circle::setCenter(double x, double y)
{
    _x = x;
    _y = y;
}

void ME_Circle::setRadius(double r)
{
    _r = r;
}

double ME_Circle::getX() const
{
    return _x;
}

double ME_Circle::getY() const
{
    return _y;
}

double ME_Circle::getRadius() const
{
    return _r;
}

bool ME_Circle::containsPoint(const ME_Vector2D* point) const
{
    return containsPoint(point->getX(), point->getY());
}

bool ME_Circle::containsPoint(double x, double y) const
{
    // check if the distance to the center is less than the radius
    x -= _x;
    y -= _y;
    return ((x*x + y*y) < _r*_r);
}

bool ME_Circle::collidesWithRectangle(const ME_Rectangle* rect) const
{
    double halfw = rect->getWidth() / 2;
    double halfh = rect->getHeight() / 2;
    // get the distance between the center of both the circle and rectangle
    double xdist = abs(rect->getX() + halfw - _x);
    double ydist = abs(rect->getY() + halfh - _y);
    // test for impossible collisions
    if ((xdist > halfw + _r) || (ydist > halfh + _r)) {
        return false;
    }
    // test for definite collisions
    if ((xdist < halfw) || (ydist < halfh)) {
        return true;
    }
    // test if the nearest corner is within the circle
    xdist -= halfw;
    ydist -= halfh;
    return ((xdist*xdist + ydist*ydist) < _r*_r);
}

bool ME_Circle::collidesWithCircle(const ME_Circle* c) const
{
    // test if the distance between centers is less
    // than the total radius
    double xd = _x - c->_x;
    double yd = _y - c->_y;
    double rd = _r + c->_r;
    return ((xd*xd + yd*yd) < rd*rd);
}
