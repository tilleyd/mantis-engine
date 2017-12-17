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

#include "mantis_stage.h"

ME_Stage::ME_Stage(ME_Framework* fw)
    : _framework(fw)
{}

ME_Stage::~ME_Stage()
{
    // delete all the entities
    for (entitymap_t::iterator it = _entities.begin();
            it != _entities.end(); ++it) {
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
