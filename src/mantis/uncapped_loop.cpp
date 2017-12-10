/*==============================================================================
 * ME_UncappedLoop timer implementation
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

#include <SDL2/SDL.h>

void ME_UncappedLoop::loop()
{
    unsigned int prev = SDL_GetTicks();
    unsigned int cur = prev;
    double period;

	while (_running) {
        // calculate the time passed from the previous iteration
        period = (cur - prev) / 1000.0;
		update(period);
		draw();
        prev = cur;
		cur = SDL_GetTicks();
	}
}
