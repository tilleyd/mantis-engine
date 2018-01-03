/*==============================================================================
 * ME_Vector implementation
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

#include <cmath>

ME_Vector2D::ME_Vector2D(double x, double y) :
    _x(x),
    _y(y)
{}

void ME_Vector2D::setX(double x)
{
    _x = x;
}

void ME_Vector2D::setY(double y)
{
    _y = y;
}

void ME_Vector2D::setValue(double x, double y)
{
    _x = x;
    _y = y;
}

double ME_Vector2D::getX() const
{
    return _x;
}

double ME_Vector2D::getY() const
{
    return _y;
}

double ME_Vector2D::getMagnitude() const
{
    return sqrt(_x * _x + _y * _y);
}

void ME_Vector2D::normalize(double newmag)
{
    double mag = getMagnitude();
    _x = (_x / mag) * newmag;
    _y = (_y / mag) * newmag;
}
