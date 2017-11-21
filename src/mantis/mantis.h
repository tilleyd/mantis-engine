/*==============================================================================
 * Mantis Engine main class headers
 *============================================================================*/

#ifndef ME_MANTIS_H
#define ME_MANTIS_H

#include <SDL2/SDL.h>
#include <map>
#include <string>

// forward declarations
class ME_Framework;
class ME_Graphics;
class ME_Stage;
class ME_Window;

#include "mantis_exception.h"
#include "mantis_image.h"
#include "mantis_timer.h"

// stagemap typedef
typedef std::map<std::string, ME_Stage*> stagemap_t;

#define DEFAULT_WIDTH  1280
#define DEFAULT_HEIGHT 720

/*==============================================================================
 * ME_Framework
 *
 *     Encapsulates majority of the engine into a single interface that should
 *     be utilized for the specific game. The framework manages the entities,
 *     stages, engine configuration and the game window.
 *============================================================================*/
class ME_Framework : public ME_IntervalObserver
{
	public:
		/*----------------------------------------------------------------------
		 * The parameters are the window title, window width and window height,
		 * where the width and height are optional.                           */
		ME_Framework(std::string title, int w = DEFAULT_WIDTH,
				int h = DEFAULT_HEIGHT);
		virtual ~ME_Framework();

		/*----------------------------------------------------------------------
		 * Start the framework with the provided FPS.                         */
		void start(unsigned int fps);
		void stop();

		/*----------------------------------------------------------------------
		 * Override from ME_IntervalObserver                                  */
		void update(ME_Interval*, double);
		void draw();

		/*----------------------------------------------------------------------
		 * Stage management functions. Each stage is associated with a tag that
		 * can be used to reference the stage. setActiveStage() brings the
		 * active stage to the foreground.                                    */
		void addStage(ME_Stage*, std::string tag);
		void setActiveStage(std::string tag);

		/*----------------------------------------------------------------------
		 * Width and height access. This is the size of the rendering canvas. */
		int getWidth() const;
		int getHeight() const;

		/*----------------------------------------------------------------------
		 * Image bank access                                                  */
		ME_ImageBank* getImageBank();

	private:
		// framework variables
		ME_Window*    _window;
		ME_Graphics*  _graphics;
		ME_Interval*  _timer;
		ME_Stage*     _stage;
		ME_ImageBank* _images;
		stagemap_t    _stages;

		// game variables
		bool          _running;
		int           _width;
		int           _height;
};

/*==============================================================================
 * ME_Graphics
 *
 *     Represents a rendering device that is associated with the window. This
 *     device is passed to all rendering functions and is used for the creation
 *     of images.
 *============================================================================*/
class ME_Graphics
{
	public:
		~ME_Graphics();

		/*----------------------------------------------------------------------
		 * Clear the rendering canvas to the current color                    */
		void clear();

		/*----------------------------------------------------------------------
		 * Color management functions                                         */
		void setColor(int r, int g, int b);
 		void setColor(int a, int r, int g, int b);

		/*----------------------------------------------------------------------
		 * Image rendering functions                                          */
		void drawImage(ME_Image*);
		void drawImage(ME_Image*, int x, int y);
		void drawImage(ME_Image*, int x, int y, int w, int h);

		/*----------------------------------------------------------------------
		 * Geometry rendering functions                                       */
		void drawRect(int x, int y, int w, int h);
		void fillRect(int x, int y, int w, int h);
		void drawLine(int x1, int y1, int x2, int y2);

		/*----------------------------------------------------------------------
		 * SDL renderer access                                                */
		SDL_Renderer* getRenderer();

	private:
		/*----------------------------------------------------------------------
		 * Only the window is allowed to create rendering devices.            */
		friend class ME_Window;
		ME_Graphics(ME_Window*);
		SDL_Renderer* _renderer;
};

/*==============================================================================
 * ME_Stage
 *
 *     Represents a room or area in the game. Stages are the main method of
 *     organizing the game logic. The framework works on one stage at a time and
 *     each stage contains has the update() and render() methods, which are
 *     called by the framework to render or progress the stage.
 *============================================================================*/
class ME_Stage
{
	public:
		ME_Stage(ME_Framework*);
		virtual ~ME_Stage();

		/*----------------------------------------------------------------------
		 * Essential game loop functions.                                     */
		virtual void update(double) = 0;
		virtual void render(ME_Graphics*) = 0;

		/*----------------------------------------------------------------------
		 * Mouse event triggered functions.                                   */
		virtual void onMouseMotion(SDL_MouseMotionEvent*) {}
		virtual void onMousePress(SDL_MouseButtonEvent*) {}
		virtual void onMouseRelease(SDL_MouseButtonEvent*) {}
		virtual void onMouseWheel(SDL_MouseWheelEvent*) {}

		/*----------------------------------------------------------------------
		 * Keyboard event triggered functions.                                */
		virtual void onKeyPress(SDL_KeyboardEvent*) {}
		virtual void onKeyRelease(SDL_KeyboardEvent*) {}

		/*----------------------------------------------------------------------
		 * Window event triggered functions.                                  */
		virtual void onWindowChange(SDL_WindowEvent*) {}

	protected:
		ME_Framework* _framework;
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
		 * SDL window access                                                  */
		SDL_Window* getWindow();
	private:
		SDL_Window*  _win;
		ME_Graphics* _graphics;
};

#endif
