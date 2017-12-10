/*==============================================================================
 * ME_Loop skeleton functions implementation
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

#include "mantis_loop.h"

#include "mantis_exception.h"
#include <SDL2/SDL.h>

void ME_Loop::start(ME_LoopObserver* obs, ME_Graphics* g)
{
    if (obs == NULL) {
        throw ME_Exception("The loop observer is NULL");
    }
    _observer = obs;
    _graphics = g;
	_running = true;
	loop();
}

void ME_Loop::stop()
{
	_running = false;
}

void ME_Loop::draw()
{
    if (_running) {
        _observer->draw();
        SDL_RenderPresent(_graphics->getSDLRenderer());
    }
}

void ME_Loop::update(double period)
{
    if (_running) {
        _observer->update(this, period);
    }
}
