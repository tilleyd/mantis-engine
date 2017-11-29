/*==============================================================================
 * ME_IntervalLoop timer implementation
 *============================================================================*/

#include "mantis_loop.h"

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
