/*==============================================================================
 * ME_Interval timer implementation
 *     Author  : Duncan Tilley
 *     Modified: 2017 Oct 30
 *============================================================================*/

#include "mantis.h"
#include "mantis_timing.h"

#include <SDL2/SDL.h>

#define MAX_FRAME_SKIPS 8

ME_Interval::ME_Interval(unsigned int freq)
	: _freq(freq)
	, _running(false)
{}

void ME_Interval::start(ME_IntervalObserver* obs)
{
	if (obs == NULL) {
		throw ME_Exception("IntervalObserver is NULL");
	}
	_running = true;
	// calculate the expected period
	unsigned int period = 1000 / _freq;
	double dperiod = 1.0 / _freq;

	unsigned int startTime = SDL_GetTicks();
	unsigned int before = startTime;
	unsigned int missed = 0;
	int oversleep = 0;
	int sleep;
	unsigned int after, skips;

	while (_running) {
		obs->update(this, dperiod);
		obs->draw();
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
			obs->update(this, dperiod);
		}
		before = SDL_GetTicks();
	}
}

void ME_Interval::stop()
{
	_running = false;
}
