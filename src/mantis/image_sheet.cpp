/*==============================================================================
 * ME_ImageSheet implementation
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

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
using std::string;

ME_ImageSheet::ME_ImageSheet(std::string path, int startx, int starty,
        int imgw, int imgh, int rows, int cols, int numimgs) :
    ME_Image(path),
    _bounds(),
    _ranges(),
    _iwidth(imgw),
    _iheight(imgh),
    _duration(1.0),
    _curFrame(0),
    _time(0.0)
{
    // check for size errors
    if (rows * cols < numimgs) {
        throw ME_Exception("There are more images than possible for rows*cols");
    }
    if (numimgs < 1) {
        throw ME_Exception("The sheet requires at least one clipped image");
    }
    // set up the clipping rectangles
    int row = 0, col = 0;
    int x, y;
    for (int i = 0; i < numimgs; ++i) {
        x = startx + col * imgw;
        y = starty + row * imgh;
        ++col;
        if (col == cols) {
            col = 0;
            ++row;
        }
        SDL_Rect* rect = new SDL_Rect();
        rect->x = x;
        rect->y = y;
        rect->w = imgw;
        rect->h = imgh;
        _bounds.push_back(rect);
    }
    setAnimationRange(IMG_RANGE_ALL);
}

ME_ImageSheet::ME_ImageSheet(std::string path, int imgw, int imgh,
        int numimgs) :
    ME_ImageSheet(path, 0, 0, imgw, imgh, numimgs, 1, numimgs)
{}

ME_ImageSheet::~ME_ImageSheet()
{
    // delete the rectangles
    for (unsigned int i = 0; i < _bounds.size(); ++i) {
		delete _bounds[i];
	}
}

int ME_ImageSheet::getWidth() const
{
    // return the clipped image size
    return _iwidth;
}

int ME_ImageSheet::getHeight() const
{
    // return the clipped image size
    return _iheight;
}

void ME_ImageSheet::draw(ME_Graphics* g)
{
    int framenum = _rangeStart + _curFrame;
    // render the entire screen with the image
    int r = SDL_RenderCopy(g->getSDLRenderer(), _texture, _bounds[framenum],
            NULL);
    if (r) {
        throw ME_Exception(SDL_GetError());
    }
}

void ME_ImageSheet::draw(ME_Graphics* g, ME_Rectangle* rect)
{
    int framenum = _rangeStart + _curFrame;
    // render at the given position with stretching
    SDL_Rect* dest = rect->getSDLRect();
    int r = SDL_RenderCopy(g->getSDLRenderer(), _texture, _bounds[framenum],
            dest);
    if (r) {
        throw ME_Exception(SDL_GetError());
    }
}

void ME_ImageSheet::setCurrentFrame(unsigned int index)
{
    if (index < _rangeLength) {
        _curFrame = index;
    }
}

void ME_ImageSheet::setAnimationDuration(double sec)
{
    _duration = sec;
}

void ME_ImageSheet::updateAnimation(double period)
{
    _time += period;
    while (_time >= _duration) {
        // advance to the next frame
        _curFrame = (_curFrame + 1) % _rangeLength;
        _time -= _duration;
    }
}

void ME_ImageSheet::addAnimationRange(int start, int end)
{
    if (end < start) {
        throw ME_Exception("Error: Invalid animation range");
    }
    animrange_t range;
    range.start = start;
    range.end = end;
    _ranges.push_back(range);
}

void ME_ImageSheet::setAnimationRange(int index)
{
    if (index == IMG_RANGE_ALL) {
        // set the all range measures
        _rangeLength = _bounds.size();
        _rangeStart = 0;
    } else {
        try {
            // set the appropriate range measures
            animrange_t cur = _ranges[index];
            _rangeLength = cur.end - cur.start + 1;
            _rangeStart = cur.start;
        } catch (...) {
            throw ME_Exception("Error: Invalid animation range index");
        }
    }
    _curRange = index;
    // modulus is used instead of setting to 0 since it looks smoother in
    // some animations, such as movement
    _curFrame %= _rangeLength;
}
