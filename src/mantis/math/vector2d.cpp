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
{
    _mag = sqrt(_x * _x + _y * _y);
}

void ME_Vector2D::setX(double x)
{
    setValue(x, _y);
}

void ME_Vector2D::setY(double y)
{
    setValue(_x, y);
}

void ME_Vector2D::setValue(double x, double y)
{
    _x = x;
    _y = y;
    _mag = sqrt(_x * _x + _y * _y);
}

double ME_Vector2D::getX() const
{
    return _x;
}

double ME_Vector2D::getY() const
{
    return _y;
}

ME_Vector2D& ME_Vector2D::operator+=(const ME_Vector2D& vec)
{
    setValue(_x + vec._x, _y + vec._y);
    return *this;
}

ME_Vector2D& ME_Vector2D::operator-=(const ME_Vector2D& vec)
{
    setValue(_x - vec._x, _y - vec._y);
    return *this;
}

ME_Vector2D& ME_Vector2D::operator*=(double val)
{
    setValue(_x * val, _y * val);
    return *this;
}

ME_Vector2D& ME_Vector2D::operator/=(double val)
{
    setValue(_x / val, _y / val);
    return *this;
}

double ME_Vector2D::getMagnitude() const
{
    return _mag;
}

void ME_Vector2D::normalize(double newmag)
{
    if (_mag != 0.0) {
        setValue((_x / _mag) * newmag, (_y / _mag) * newmag);
    }
}

double ME_Vector2D::angleBetween(const ME_Vector2D* vec) const
{
    if (_mag != 0.0 && vec->_mag != 0.0) {
        double rad = acos(dotProduct(vec) / (_mag * vec->_mag));
        return rad * 180.0 / M_PI;
    } else {
        return 0.0;
    }
}

double ME_Vector2D::dotProduct(const ME_Vector2D* vec) const
{
    return _x * vec->_x + _y * vec->_y;
}
