/*==============================================================================
 * ME_Loop skeleton functions implementation
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
