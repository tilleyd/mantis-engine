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

#include "mantis_ui.h"

ME_UiComponent::ME_UiComponent() :
    _focused(false),
    _hovered(false),
    _bounds(0, 0, 10, 10),
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

bool ME_UiComponent::isFocused()
{
    return _focused;
}

void ME_UiComponent::setHover(bool h)
{
    _hovered = h;
}

bool ME_UiComponent::isHovered()
{
    return _hovered;
}

void ME_UiComponent::setSize(int w, int h)
{
    _bounds.setWidth(w);
    _bounds.setHeight(h);
}

void ME_UiComponent::setPosition(int x, int y)
{
    _bounds.setX(x);
    _bounds.setY(y);
}

void ME_UiComponent::setBounds(int x, int y, int w, int h)
{
    _bounds.setX(x);
    _bounds.setY(y);
    _bounds.setWidth(w);
    _bounds.setHeight(h);
}

void ME_UiComponent::setBounds(const ME_Rectangle* rect)
{
    _bounds = *rect;
}

void ME_UiComponent::setCenterPosition(int x, int y)
{
    _bounds.setX(x - (_bounds.getWidth() / 2));
    _bounds.setY(y - (_bounds.getHeight() / 2));
}

void ME_UiComponent::addUiObserver(ME_UiObserver* obs)
{
    _observers.push_back(obs);
}

void ME_UiComponent::performAction()
{
    for (unsigned int i = 0; i < _observers.size(); ++i) {
        _observers[i]->uiActionPerformed();
    }
}
