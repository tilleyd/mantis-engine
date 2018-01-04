/*==============================================================================
 * ME_Animation implementation
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

ME_Animation::ME_Animation(ME_ImageSheet* sheet) :
    _sheet(sheet),
    _duration(1.0),
    _time(0.0),
    _curFrame(0)
{
    setAnimationRange(IMG_RANGE_ALL);
}

void ME_Animation::setCurrentFrame(int index)
{
    if (index < _rangeLength) {
        _sheet->setCurrentFrame(_rangeStart + index);
        _curFrame = index;
    }
}

void ME_Animation::setAnimationDuration(double sec)
{
    _duration = sec;
}

void ME_Animation::updateAnimation(double period)
{
    _time += period;
    while (_time >= _duration) {
        // advance to the next frame
        _curFrame = (_curFrame + 1) % _rangeLength;
        _time -= _duration;
    }
    _sheet->setCurrentFrame(_rangeStart + _curFrame);
}

void ME_Animation::addAnimationRange(int start, int end)
{
    if (end < start) {
        throw ME_Exception("Error: Invalid animation range");
    }
    animrange_t range;
    range.start = start;
    range.end = end;
    _ranges.push_back(range);
}

void ME_Animation::setAnimationRange(int index)
{
    if (index == IMG_RANGE_ALL) {
        // set the all range measures
        _rangeLength = _sheet->getNumImages();
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

ME_Image* ME_Animation::getImage()
{
    return _sheet;
}
