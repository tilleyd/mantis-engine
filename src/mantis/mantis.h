/*==============================================================================
 * Mantis Engine main class headers
 *     Author  : Duncan Tilley
 *     Modified: 2017 Nov 19
 *============================================================================*/

#ifndef ME_MANTIS_H
#define ME_MANTIS_H

#include <string>
#include <SDL2/SDL.h>

#include "mantis_image.h"
#include "mantis_timer.h"

// forward declarations
class ME_Framework;
class ME_Stage;
class ME_Exception;
class ME_Window;


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
		 * The parameters are the game name (in lowercase without spaces) and
		 * the title for the window. The game name is used to create the game
		 * configuration folder.                                              */
		ME_Framework(std::string gn, std::string wn);
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
		 * Stage management functions.                                        */
		void addStage(ME_Stage*);
		void removeStage(int sid);
		void setCurrentStage(int sid);

		/*----------------------------------------------------------------------
		 * Image management functions. Each image is represented by a tag, so
		 * getImage() returns the image with the given name and loadImage()
		 * loads an image from the provided filename and gives it the tag
		 * specified in the second parameter.                                 */
		const ME_Image& getImage(std::string tag) const;
		void loadImage(std::string path, std::string tag);

	private:
		ME_Window*    _window;
		ME_Interval*  _timer;
		ME_ImageBank* _images;
		ME_Stage**    _stages;
		bool          _running;
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
		virtual void update(double) = 0;
		virtual void render() = 0;
	protected:
		ME_Framework* _framework;
};


/*==============================================================================
 * ME_Exception
 *
 *     Represents an exception/error used for try/catch statements. Contains
 *     an error message string.
 *============================================================================*/
class ME_Exception
{
	public:
		ME_Exception(std::string);
		const std::string& getMessage() const;
	private:
		std::string _mesg;
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
	private:
		SDL_Window* _win;
};

#endif
