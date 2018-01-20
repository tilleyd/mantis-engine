/*==============================================================================
 * ME_Color implementation
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

#include "mantis.h"

ME_Color::ME_Color(int a, int r, int g, int b) :
    _color(new SDL_Color)
{
    setColor(a, r, g, b);
}

ME_Color::ME_Color(int r, int g, int b) :
    ME_Color(0xff, r, g, b)
{}

ME_Color::ME_Color(int a, int rgb) :
    ME_Color(a, rgb, rgb, rgb)
{}

ME_Color::ME_Color(int rgb) :
    ME_Color(0xff, rgb, rgb, rgb)
{}

ME_Color::ME_Color(const ME_Color& other) :
    ME_Color(other.getAlpha(), other.getRed(),
            other.getGreen(), other.getBlue())
{}

ME_Color::~ME_Color()
{
    delete _color;
    _color = NULL;
}

ME_Color& ME_Color::operator=(const ME_Color& other)
{
    setColor(other.getAlpha(), other.getRed(),
            other.getGreen(), other.getBlue());
    return *this;
}

int ME_Color::getAlpha() const
{
    return _color->a;
}

int ME_Color::getRed() const
{
    return _color->r;
}

int ME_Color::getGreen() const
{
    return _color->g;
}

int ME_Color::getBlue() const
{
    return _color->b;
}

void ME_Color::setColor(ME_Color* clr)
{
    setColor(clr->getAlpha(), clr->getRed(), clr->getGreen(), clr->getBlue());
}

void ME_Color::setColor(int a, int r, int g, int b)
{
    setAlpha(a);
    setRed(r);
    setGreen(g);
    setBlue(b);
}

void ME_Color::setColor(int r, int g, int b)
{
    setColor(_color->a, r, g, b);
}

void ME_Color::setColor(int a, int rgb)
{
    setColor(a, rgb, rgb, rgb);
}

void ME_Color::setColor(int rgb)
{
    setColor(_color->a, rgb);
}

void ME_Color::setAlpha(int a)
{
    if (a < 0 || a > 0xff) {
        throw ME_Exception("Error: Invalid value for alpha channel.");
    }
    _color->a = a;
}

void ME_Color::setRed(int r)
{
    if (r < 0 || r > 0xff) {
        throw ME_Exception("Error: Invalid value for red channel.");
    }
    _color->r = r;
}

void ME_Color::setGreen(int g)
{
    if (g < 0 || g > 0xff) {
        throw ME_Exception("Error: Invalid value for green channel.");
    }
    _color->g = g;
}

void ME_Color::setBlue(int b)
{
    if (b < 0 || b > 0xff) {
        throw ME_Exception("Error: Invalid value for blue channel.");
    }
    _color->b = b;
}

SDL_Color* ME_Color::getSDLColor()
{
    return _color;
}
