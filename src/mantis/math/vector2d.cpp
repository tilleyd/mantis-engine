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

ME_Vector2D ME_Vector2D::operator+(ME_Vector2D vec)
{
    return ME_Vector2D(_x + vec._x, _y + vec._y);
}

ME_Vector2D ME_Vector2D::operator-(ME_Vector2D vec)
{
    return ME_Vector2D(_x - vec._x, _y - vec._y);
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
        if (vec->_y < _y) {
            rad = -rad;
        }
        return rad * 180.0 / M_PI;
    } else {
        return 0.0;
    }
}

double ME_Vector2D::dotProduct(const ME_Vector2D* vec) const
{
    return _x * vec->_x + _y * vec->_y;
}

bool ME_Vector2D::withinAngle(double angle, const ME_Vector2D* vec)
{
    return (abs(angleBetween(vec)) < angle);
}

bool ME_Vector2D::withinAngle(double angle, const ME_Rectangle* rec)
{
    // get the angle to each corner and check if it is within the cone
    ME_Vector2D corner(rec->getX(), rec->getY());
    double cor1 = angleBetween(&corner);
    if (abs(cor1) < angle) {
        return true;
    }
    corner.setY(rec->getY() + rec->getHeight());
    double cor2 = angleBetween(&corner);
    if (abs(cor2) < angle) {
        return true;
    }
    corner.setX(rec->getX() + rec->getWidth());
    double cor3 = angleBetween(&corner);
    if (abs(cor3) < angle) {
        return true;
    }
    corner.setY(rec->getY());
    double cor4 = angleBetween(&corner);
    if (abs(cor4) < angle) {
        return true;
    }

    // check if there is at least one corner with a different sign than the
    // others, which checks if the cone goes through the rectangle without
    // touching any corners
    bool cor1neg = (cor1 < 0.0);
    return ((cor1neg != (cor2 < 0.0)) || (cor1neg != (cor3 < 0.0)) ||
            (cor1neg != (cor4 < 0.0)));
}

bool ME_Vector2D::withinAngle(double angle, const ME_Circle*)
{
    // TODO
    return false;
}
