/*==============================================================================
 * Mantis Engine main class headers
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

#ifndef ME_MAIN_H
#define ME_MAIN_H

#include <map>

// datastruct typedefs
typedef std::map<std::string, ME_Stage*> stagemap_t;

#define DEFAULT_WIDTH  1280
#define DEFAULT_HEIGHT 720

#define WM_FULLSCREEN 0
#define WM_BORDERLESS 1
#define WM_WINDOWED   2

#define FPS_VSYNC    -1 // any negative FPS is used as VSync
#define FPS_UNCAPPED  0

/*==============================================================================
 * ME_Framework
 *
 *     Encapsulates majority of the engine into a single interface that should
 *     be utilized for the specific game. The framework manages the entities,
 *     stages, engine configuration and the game window.
 *============================================================================*/
class ME_Framework : public ME_LoopObserver
{
	public:
		/*----------------------------------------------------------------------
		 * The parameters are the window title, window width and window height,
		 * where the width and height are optional.                           */
		ME_Framework(std::string title, int w = DEFAULT_WIDTH,
				int h = DEFAULT_HEIGHT);
		virtual ~ME_Framework();

		/*----------------------------------------------------------------------
		 * Start the framework with the provided FPS. See the FPS types above
		 * for VSync or Uncapped.                                             */
		void start(int fps);
		void stop();

		/*----------------------------------------------------------------------
		 * Dynamic contex changes, note that these require reloading images in
		 * most cases.                                                       */
		void setFPS(int fps);
		void setWindowMode(int mode);

		/*----------------------------------------------------------------------
		 * Override from ME_IntervalObserver                                  */
		void update(ME_Loop*, double);
		void draw();

		/*----------------------------------------------------------------------
		 * Stage management functions. Each stage is associated with a tag that
		 * can be used to reference the stage. setActiveStage() brings the
		 * active stage to the foreground.                                    */
		void addStage(ME_Stage*, std::string tag);
		void setActiveStage(std::string tag);
        /* Hover stages are a way to draw two overlapping stages (as a sort of
         * floating menu) with the option of still updating the background stage
         * or pausing (but still rendering) it.                               */
        void setHoverStage(std::string tag, bool update);
        void clearHoverStage();

		/*----------------------------------------------------------------------
		 * Width and height access. This is the size of the rendering canvas. */
		int getWidth() const;
		int getHeight() const;
		int getCenterX() const;
		int getCenterY() const;

		/*----------------------------------------------------------------------
		 * Member access                                                      */
		ME_Window* getWindow();
		ME_Graphics* getGraphics();
		int getWindowMode() const;
		int getFPS() const;

	private:
		// framework variables
		ME_Window*    _window;
		ME_Graphics*  _graphics;
		ME_Loop*      _loop;
		ME_Stage*     _stage;
        ME_Stage*     _hoverstage;
		stagemap_t    _stages;
        bool          _updatea;

		// reload check variables
		bool          _atstart;
		bool          _vsync;
		int           _wmode;
		int           _fps;

		// game variables
		bool          _running;
		int           _width;
		int           _height;
		int           _centerx;
		int           _centery;
};

/*==============================================================================
 * ME_Window
 *
 *     Creates a window using the SDL2 library with the provided width and
 *     height and title.
 *============================================================================*/
class ME_Window
{
	public:
		ME_Window(std::string t, unsigned int w, unsigned int h);
		~ME_Window();

		ME_Graphics* getGraphics();

		/*----------------------------------------------------------------------
		 * State modifications                                                */
		void setSize(int w, int h);
		void setWindowMode(int);

		/*----------------------------------------------------------------------
		 * SDL window access                                                  */
		SDL_Window* getSDLWindow();
	private:
		SDL_Window*  _win;
		SDL_Surface* _surf;
		ME_Graphics* _graphics;
};

#endif
