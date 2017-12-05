/*==============================================================================
 * Mantis Engine main class headers
 *============================================================================*/

#ifndef ME_MANTIS_H
#define ME_MANTIS_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <map>
#include <stack>
#include <string>

// forward declarations
class ME_Framework;
class ME_Graphics;
class ME_Stage;
class ME_Window;

#include "mantis_exception.h"
#include "mantis_image.h"
#include "mantis_loop.h"
#include "math/mantis_math.h"

// datastruct typedefs
typedef std::map<std::string, ME_Stage*> stagemap_t;
typedef std::stack<std::string> backstack_t;

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
		/* nextStage() and backStage() make use of the backstack for stage
		 * selection and swapping.                                            */
		void nextStage(std::string tag);
		void backStage();

		/*----------------------------------------------------------------------
		 * Width and height access. This is the size of the rendering canvas. */
		int getWidth() const;
		int getHeight() const;

		/*----------------------------------------------------------------------
		 * Member access                                                      */
		ME_Window* getWindow();
		ME_Graphics* getGraphics();
		int getWindowMode() const;

	private:
		// framework variables
		ME_Window*    _window;
		ME_Graphics*  _graphics;
		ME_Loop*      _loop;
		ME_Stage*     _stage;
		std::string   _stagetag;
		stagemap_t    _stages;
		backstack_t   _backstack;

		// reload check variables
		bool          _atstart;
		bool          _vsync;
		int           _wmode;

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
		void drawRect(const ME_Rectangle*);
		void drawRect(int x, int y, int w, int h);
		void fillRect(const ME_Rectangle*);
		void fillRect(int x, int y, int w, int h);
		void drawLine(int x1, int y1, int x2, int y2);

		/*----------------------------------------------------------------------
		 * Text rendering functions                                           */
		void setFont(std::string, int);
		void drawText(int x, int y, std::string);

		/*----------------------------------------------------------------------
		 * SDL renderer access                                                */
		SDL_Renderer* getSDLRenderer();
		void recreateSDLRenderer(ME_Window*, bool vsync);

	private:
		/*----------------------------------------------------------------------
		 * Only the window is allowed to create rendering devices.            */
		friend class ME_Window;
		ME_Graphics(ME_Window*);
		SDL_Renderer* _renderer;
		SDL_Color*    _color;
		TTF_Font*     _font;
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
		 * Essential resource functions (esp. image allocation).              */
		virtual void allocateResources(ME_Graphics*) = 0;
		virtual void deallocateResources() = 0;

		/*----------------------------------------------------------------------
		 * Stage event triggered functions.                                   */
		virtual void onActivate() {}
		virtual void onDeactivate() {}

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
