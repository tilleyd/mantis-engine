/*==============================================================================
 * ME_UiComponent implementation
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

ME_UiComponent::ME_UiComponent():
    _bounds(0, 0, 10, 10),
    _focused(false),
    _hovered(false),
    _enabled(true),
    _observers()
{}

ME_UiComponent::~ME_UiComponent()
{}

void ME_UiComponent::update(double period)
{}

void ME_UiComponent::render(ME_Graphics* g)
{
    // this is a default, ugly render which should definitely be replaced
    if (_hovered) {
        g->setColor(0xff, 0xff, 0xff);
    } else {
        g->setColor(0xff, 0x00, 0x00);
    }
    g->drawRect(&_bounds);
}

void ME_UiComponent::requestFocus()
{
    // TODO some static lock, some focus list
    //if ()...
}

bool ME_UiComponent::isFocused() const
{
    return _focused;
}

void ME_UiComponent::setHovered(bool h)
{
    _hovered = h;
}

bool ME_UiComponent::isHovered() const
{
    return _hovered;
}

void ME_UiComponent::setEnabled(bool e)
{
    _enabled = e;
}

bool ME_UiComponent::isEnabled() const
{
    return _enabled;
}

void ME_UiComponent::setSize(int w, int h)
{
    // Although it seems tedious to use setBounds instead of setting it directly
    // with the bounds object, this allows easy overriding of only the
    // setBounds() function, instead of all accessors.
    setBounds(_bounds.getX(), _bounds.getY(), w, h);
}

void ME_UiComponent::setPosition(int x, int y)
{
    // see the comment under setSize() above
    setBounds(x, y, _bounds.getWidth(), _bounds.getHeight());
}

void ME_UiComponent::setBounds(const ME_Rectangle* r)
{
    // see the comment under setSize() above
    setBounds(r->getX(), r->getY(), r->getWidth(), r->getHeight());
}

void ME_UiComponent::setBounds(int x, int y, int w, int h)
{
    _bounds.setX(x);
    _bounds.setY(y);
    _bounds.setWidth(w);
    _bounds.setHeight(h);
}

void ME_UiComponent::setCenterPosition(int x, int y)
{
    setPosition(x - (_bounds.getWidth() / 2), y - (_bounds.getHeight() / 2));
}

bool ME_UiComponent::containsPoint(int x, int y) const
{
    return _bounds.containsPoint(x, y);
}

const ME_Rectangle* ME_UiComponent::getBounds() const
{
    return &_bounds;
}

void ME_UiComponent::addUiObserver(ME_UiObserver* obs)
{
    _observers.push_back(obs);
}

void ME_UiComponent::performAction(int action)
{
    for (unsigned int i = 0; i < _observers.size(); ++i) {
        _observers[i]->uiActionPerformed(this, action);
    }
}
