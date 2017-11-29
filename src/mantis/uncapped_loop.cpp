/*==============================================================================
 * ME_UncappedLoop timer implementation
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
