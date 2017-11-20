/*==============================================================================
 * ME_Window implementation
 *     Modified: 2017 Nov 20
 *============================================================================*/

#include "mantis.h"

#include <SDL2/SDL.h>
#include <map>
#include <string>
using std::string;

#define DEFAULT_WIDTH  1280
#define DEFAULT_HEIGHT 720

ME_Framework::ME_Framework(string gn, string wn)
	: _window(NULL)
	, _timer(NULL)
	, _images(NULL)
	, _stage(NULL)
	, _stages()
	, _running(false)
{
	// initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		throw ME_Exception(SDL_GetError());
	}

	// TODO read configuration details

	// create the window
	_window = new ME_Window(wn, DEFAULT_WIDTH, DEFAULT_HEIGHT);
}

ME_Framework::~ME_Framework()
{
	_running = false;
	if (_timer) {
		_timer->stop();
		delete _timer;
		_timer = NULL;
	}
	if (_window) {
		delete _window;
		_window = NULL;
	}
	// delete stages
	for (stagemap_t::iterator it = _stages.begin(); it != _stages.end(); ++it) {
		delete it->second;
	}
	// clean up SDL
	SDL_Quit();
}

void ME_Framework::start(unsigned int freq)
{
	if (_timer == NULL) {
		_running = true;
		_timer = new ME_Interval(freq);
		_timer->start(this);
	}
}

void ME_Framework::stop()
{
	_running = false;
}

void ME_Framework::update(ME_Interval* tim, double period)
{
	SDL_Event e;
	// poll SDL events
	while (SDL_PollEvent(&e) != 0) {
		switch (e.type) {
			case SDL_QUIT:
				stop();
				break;
		}
	}
	// stop the game if necessary
	if (!_running) {
		tim->stop();
	}
	// delegate update to the current stage
	if (_stage) {
		_stage->update(period);
	}
}

void ME_Framework::draw()
{
	// delegate to stages and draw to window
	if (_stage) {
		_stage->render();
		// TODO draw to window
	}
}

void ME_Framework::addStage(ME_Stage* stage, std::string tag)
{
	_stages[tag] = stage;
}

void ME_Framework::setActiveStage(std::string tag)
{
	try {
		ME_Stage* stage = _stages.at(tag);
		_stage = stage;
	} catch (...) {}
}

const ME_Image& ME_Framework::getImage(string tag) const
{
	// TODO
}

void ME_Framework::loadImage(string path, string tag)
{
	// TODO
}
