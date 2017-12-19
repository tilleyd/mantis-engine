/*==============================================================================
 * ME_IntervalLoop timer implementation
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

#define MAX_FRAME_SKIPS 8

ME_IntervalLoop::ME_IntervalLoop(unsigned int fps)
	: _fps(fps)
{}

void ME_IntervalLoop::loop()
{
	// calculate the expected period
	unsigned int period = 1000 / _fps;
	double dperiod = 1.0 / _fps;

	unsigned int startTime = SDL_GetTicks();
	unsigned int before = startTime;
	unsigned int missed = 0;
	int oversleep = 0;
	int sleep;
	unsigned int after, skips;

	while (_running) {
		update(dperiod);
		draw();
		after = SDL_GetTicks();
		sleep = period - (after - before) - oversleep;
		if (sleep > 0) {
			// blocks for the remaining time
			SDL_Delay(sleep);
			// check oversleep caused by OS scheduling
			oversleep = SDL_GetTicks() - after - sleep;
		} else {
			// add the missed sleep time
			missed -= sleep;
		}
		// catch up missed frames without drawing
		skips = 0;
		while (missed >= period && skips < MAX_FRAME_SKIPS) {
			++skips;
			missed -= period;
			update(dperiod);
		}
		before = SDL_GetTicks();
	}
}
