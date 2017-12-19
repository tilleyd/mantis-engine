/*==============================================================================
 * ME_UiButton implementation
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

#define DEFAULT_HPAD 5
#define DEFAULT_VPAD 5

ME_UiButton::ME_UiButton(std::string label):
    _label(label),
    _hpad(DEFAULT_HPAD),
    _vpad(DEFAULT_VPAD),
    _labelw(-1),
    _labelh(-1)
{}

ME_UiButton::~ME_UiButton()
{}

void ME_UiButton::render(ME_Graphics* g)
{
    // lazily initialize the label metrics
    if (_labelw < 0) {
        getLabelMetrics(g);
    }
    // draw a rectangle
    g->drawRect(&_bounds);
    // draw the label
    if (_labelw + _hpad > _bounds.getWidth() ||
            _labelh + _vpad > _bounds.getHeight()) {
        // clip the text inside the boundaries
        ME_Rectangle* clip = new ME_Rectangle(0, 0, _bounds.getWidth() - _hpad,
                _bounds.getHeight() - _vpad);
        g->drawText(_bounds.getX() + _hpad, _bounds.getY() + _vpad, _label,
                clip);
    } else {
        // draw unclipped text
        g->drawText(_bounds.getX() + _hpad, _bounds.getY() + _vpad, _label);
    }
}

void ME_UiButton::adjustSizeToFont(ME_Graphics* g)
{
    getLabelMetrics(g);
    setSize(_labelw + 2*_hpad, _labelh + 2*_vpad);
}

void ME_UiButton::setPadding(int hpad, int vpad)
{
    _vpad = vpad;
    _hpad = hpad;
}

void ME_UiButton::getLabelMetrics(ME_Graphics* g)
{
    _labelw = g->getTextWidth(_label);
    _labelh = g->getTextHeight(_label);
}
