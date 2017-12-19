/*==============================================================================
 * ME_Stage implementation
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

ME_Stage::ME_Stage(ME_Framework* fw):
    _framework(fw),
    _entities(),
    _uicomps(),
    _hovered(NULL),
    _pressed(NULL)
{}

ME_Stage::~ME_Stage()
{
    // delete all the entities
    for (entitymap_t::iterator it = _entities.begin();
            it != _entities.end(); ++it) {
		delete it->second;
	}
    // delete all the ui components
    for (uimap_t::iterator it = _uicomps.begin();
            it != _uicomps.end(); ++it) {
		delete it->second;
	}
}

void ME_Stage::updateEntities(double period)
{
    // update all the entities
    for (entitymap_t::iterator it = _entities.begin();
            it != _entities.end(); ++it) {
		it->second->update(period);
	}
}

void ME_Stage::renderEntities(ME_Graphics* g)
{
    // render all the entities
    for (entitymap_t::iterator it = _entities.begin();
            it != _entities.end(); ++it) {
		it->second->render(g);
	}
}

void ME_Stage::renderUiComponents(ME_Graphics* g)
{
    // render all the ui components
    for (uimap_t::iterator it = _uicomps.begin();
            it != _uicomps.end(); ++it) {
        it->second->render(g);
    }
}

void ME_Stage::addEntity(ME_Entity* en, std::string tag)
{
    if (en) {
        _entities[tag] = en;
        en->_framework = _framework;
        en->_stage = this;
    } else {
        throw ME_Exception("Error: Null entity can not be added");
    }
}

void ME_Stage::removeEntity(std::string tag)
{
    try {
        ME_Entity* en = _entities.at(tag);
        delete en;
        _entities.erase(tag);
    } catch (...) {
        throw ME_Exception("Error: Invalid entity tag");
    }
}

ME_Entity* ME_Stage::getEntity(std::string tag)
{
    try {
        ME_Entity* en = _entities.at(tag);
        return en;
    } catch (...) {
        throw ME_Exception("Error: Invalid entity tag");
    }
}

void ME_Stage::addUiComponent(ME_UiComponent* comp, std::string tag)
{
    if (comp) {
        _uicomps[tag] = comp;
    } else {
        throw ME_Exception("Error: Null UI component can not be added");
    }
}

void ME_Stage::removeUiComponent(std::string tag)
{
    try {
        ME_UiComponent* comp = _uicomps.at(tag);
        delete comp;
        _uicomps.erase(tag);
    } catch (...) {
        throw ME_Exception("Error: Invalid UI component tag");
    }
}

ME_UiComponent* ME_Stage::getUiComponent(std::string tag)
{
    try {
        ME_UiComponent* comp = _uicomps.at(tag);
        return comp;
    } catch (...) {
        throw ME_Exception("Error: Invalid UI component tag");
    }
}

void ME_Stage::checkUiMouseHover(SDL_MouseMotionEvent* e)
{
    int x = e->x;
    int y = e->y;
    if (_hovered) {
        // check if the current is still hovered over
        if (!(_hovered->containsPoint(x, y))) {
            _hovered->setHovered(false);
            _hovered = NULL;
        }
    }
    if (!_hovered) {
        // check for any hovered component
        for (uimap_t::iterator it = _uicomps.begin();
                it != _uicomps.end(); ++it) {
            ME_UiComponent* c = it->second;
            if (c->isEnabled() && c->containsPoint(x, y)) {
                _hovered = c;
                _hovered->setHovered(true);
                return;
            }
    	}
    }
}

void ME_Stage::checkUiMousePress(SDL_MouseButtonEvent* e)
{
    if (_hovered) {
        // set the hovered component as pressed, but wait for the mouse release
        _pressed = _hovered;
    }
}

void ME_Stage::checkUiMouseRelease(SDL_MouseButtonEvent* e)
{
    if (_hovered) {
        // check that the hovered component is the pressed component
        // this is checked in case the mouse leaves the button before release
        if (_hovered == _pressed && _pressed->isEnabled()) {
            _pressed->performAction(UI_MOUSE_PRESSED);
        }
        _pressed = NULL;
    }
}
