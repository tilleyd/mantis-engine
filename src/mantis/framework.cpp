/*==============================================================================
 * ME_Window implementation
 *============================================================================*/

#include "mantis.h"

#include "mantis_exception.h"
#include <SDL2/SDL.h>
#include <string>
using std::string;

#define DEFAULT_WIDTH  1280
#define DEFAULT_HEIGHT 720

ME_Framework::ME_Framework(string gn, string wn)
	: _timer(NULL)
	, _stage(NULL)
	, _stages()
	, _running(false)
{
	// initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		throw ME_Exception(SDL_GetError());
	}

	// TODO read configuration details

	// initialize members
	_window = new ME_Window(wn, DEFAULT_WIDTH, DEFAULT_HEIGHT);
	_width = DEFAULT_WIDTH;
	_height = DEFAULT_HEIGHT;
	_graphics = _window->getGraphics();
	_images = new ME_ImageBank(_graphics);
}

ME_Framework::~ME_Framework()
{
	_running = false;
	if (_window) {
		delete _window;
		_window = NULL;
	}
	if (_timer) {
		_timer->stop();
		delete _timer;
		_timer = NULL;
	}
	if (_images) {
		delete _images;
		_images = NULL;
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
		_stage->render(_graphics);
		SDL_RenderPresent(_graphics->getRenderer());
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
	} catch (...) {
		throw ME_Exception("Error: Invalid stage tag");
	}
}

int ME_Framework::getWidth() const
{
	return _width;
}

int ME_Framework::getHeight() const
{
	return _height;
}

ME_ImageBank* ME_Framework::getImageBank()
{
	return _images;
}
