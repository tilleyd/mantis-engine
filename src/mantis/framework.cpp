/*==============================================================================
 * ME_Window implementation
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

#include "mantis_exception.h"
#include <SDL2/SDL.h>
#include <string>
using std::string;

ME_Framework::ME_Framework(string wn, int w, int h)
	: _loop(NULL)
	, _stage(NULL)
	, _hoverstage(NULL)
	, _stages()
	, _updatea(true)
	, _atstart(true)
	, _wmode(0)
	, _fps(0)
	, _running(false)
	, _width(w)
	, _height(h)
	, _centerx(w / 2)
	, _centery(h / 2)
{
	// initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		throw ME_Exception(SDL_GetError());
	}

	// initialize members
	_window = new ME_Window(wn, w, h);
	_graphics = _window->getGraphics();
}

ME_Framework::~ME_Framework()
{
	if (_loop) {
		_loop->stop();
		delete _loop;
		_loop = NULL;
	}
	_running = false;
	if (_window) {
		delete _window;
		_window = NULL;
	}
	// delete stages
	for (stagemap_t::iterator it = _stages.begin(); it != _stages.end(); ++it) {
		it->second->deallocateResources();
		delete it->second;
	}
	// clean up SDL
	SDL_Quit();
}

void ME_Framework::start(int fps)
{
	setFPS(fps);
}

void ME_Framework::stop()
{
	_running = false;
}

void ME_Framework::setFPS(int fps)
{
	_fps = fps;
	// remove the old timer
	if (_loop) {
		_loop->stop();
		delete _loop;
		_loop = NULL;
	}

	// choose the new timer
	bool vsync = (fps < 0);
	if (fps <= 0) { // FPS_VSYNC or FPS_UNCAPPED
		// use an uncapped loop timer
		_loop = new ME_UncappedLoop();
	} else {
		// use a capped loop timer
		_loop = new ME_IntervalLoop((unsigned int)fps);
	}

	// check if a reload is necessary
	if (_atstart || (vsync != _vsync)) { // game images need to be reloaded
		if (_stage) {
			_stage->deallocateResources();
		}
		// recreate the graphics device renderer to reflect VSync changes
		_graphics->recreateSDLRenderer(_window, vsync);
		if (_stage) {
			_stage->allocateResources(_graphics);
			if (!_running) { // then this is the first activation
				_stage->onActivate();
			}
		}
		_vsync = vsync;
		_atstart = false;
	}

	// start (or 'continue') the timer
	_running = true;
	_loop->start(this, _graphics);
}

void ME_Framework::setWindowMode(int mode)
{
	// TODO check if a reload is necessary on Windows
	/*if (_stage) {
		_stage->deallocateResources();
	}*/
	_window->setWindowMode(mode);
	/*if (_stage) {
		_stage->allocateResources(_graphics);
	}*/
	_wmode = mode;
}

void ME_Framework::update(ME_Loop* tim, double period)
{
	SDL_Event e;
	// poll SDL events
	while (SDL_PollEvent(&e) != 0) {
		// determine the focused stage (hover or active)
		ME_Stage* cur = _hoverstage ? _hoverstage : _stage;
		if (e.type == SDL_QUIT) {
			stop(); // TODO stop listening/interrupting
			break;
		} else if (cur) {
			switch (e.type) {
				case SDL_KEYDOWN:
					cur->onKeyPress((SDL_KeyboardEvent*)&e);
					break;
				case SDL_KEYUP:
					cur->onKeyRelease((SDL_KeyboardEvent*)&e);
					break;
				case SDL_MOUSEMOTION:
					cur->checkUiMouseHover((SDL_MouseMotionEvent*)&e);
					cur->onMouseMotion((SDL_MouseMotionEvent*)&e);
					break;
				case SDL_MOUSEBUTTONDOWN:
					cur->checkUiMousePress((SDL_MouseButtonEvent*)&e);
					cur->onMousePress((SDL_MouseButtonEvent*)&e);
					break;
				case SDL_MOUSEBUTTONUP:
					cur->checkUiMouseRelease((SDL_MouseButtonEvent*)&e);
					cur->onMouseRelease((SDL_MouseButtonEvent*)&e);
					break;
				case SDL_MOUSEWHEEL:
					cur->onMouseWheel((SDL_MouseWheelEvent*)&e);
					break;
				case SDL_WINDOWEVENT:
					// check for resizes
					if (e.window.event == SDL_WINDOWEVENT_RESIZED ||
							e.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
						_width = e.window.data1;
						_height = e.window.data2;
						_centerx = _width / 2;
						_centery = _height / 2;
					}
					cur->onWindowChange((SDL_WindowEvent*)&e);
			}
		}
	}
	// stop the game if necessary
	if (!_running) {
		tim->stop();
	}
	// delegate update to the current stage
	if (_updatea && _stage) {
		_stage->update(period);
	}
	// update the hover stage
	if (_hoverstage) {
		_hoverstage->update(period);
	}
}

void ME_Framework::draw()
{
	// delegate to stages and draw to window
	if (_stage) {
		_stage->render(_graphics);
	}
	if (_hoverstage) {
		_hoverstage->render(_graphics);
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
		if (_stage) {
			_stage->onDeactivate();
			_stage->deallocateResources();
		}
		_stage = stage;
		if (_stage) {
			if (_running) {
				_stage->allocateResources(_graphics);
				_stage->onActivate();
			}
		}
	} catch (...) {
		throw ME_Exception("Error: Invalid stage tag");
	}
}

void ME_Framework::setHoverStage(std::string tag, bool updatea)
{
	try {
		ME_Stage* h = _stages.at(tag);
		if (_hoverstage) {
			_hoverstage->onDeactivate();
			_hoverstage->deallocateResources();
		}
		_hoverstage = h;
		if (_hoverstage) {
			if (_running) {
				_hoverstage->allocateResources(_graphics);
				_hoverstage->onActivate();
			}
			_updatea = updatea;
		} else {
			_updatea = true;
		}
	} catch (...) {
		throw ME_Exception("Error: Invalid (hover) stage tag");
	}
}

void ME_Framework::clearHoverStage()
{
	if (_hoverstage) {
		_hoverstage->onDeactivate();
		_hoverstage->deallocateResources();
		_hoverstage = NULL;
	}
	_updatea = true;
}

int ME_Framework::getWidth() const
{
	return _width;
}

int ME_Framework::getHeight() const
{
	return _height;
}

int ME_Framework::getCenterX() const
{
	return _centerx;
}

int ME_Framework::getCenterY() const
{
	return _centery;
}

ME_Window* ME_Framework::getWindow()
{
	return _window;
}

ME_Graphics* ME_Framework::getGraphics()
{
	return _graphics;
}

int ME_Framework::getWindowMode() const
{
	return _wmode;
}

int ME_Framework::getFPS() const
{
	return _fps;
}
