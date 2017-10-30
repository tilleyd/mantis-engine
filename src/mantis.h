/*==============================================================================
 * Mantis Engine main class headers
 *     Author  : Duncan Tilley
 *     Modified: 2017 Oct 30
 *============================================================================*/

#ifndef ME_MANTIS_H
#define ME_MANTIS_H

#include <string>
#include <SDL2/SDL.h>

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

// forward declaration
class ME_IntervalObserver;

/*==============================================================================
 * ME_Interval
 *
 *     Used for calling a provided function periodically. It is recommended to
 *     use this class to control game FPS and update intervals if you do not
 *     make use of VSync.
 *============================================================================*/
class ME_Interval
{
	public:
		/*----------------------------------------------------------------------
		 * Creates an interval timer with a provided frequency.
		 */
		ME_Interval(unsigned int);

		/*----------------------------------------------------------------------
		 * start() Starts the timer and periodically calls the timestep() method
		 * on the provided ME_IntervalObserver. Note that start() blocks and can
		 * only be stopped by calling stop(). */
		void start(ME_IntervalObserver*);
		void stop();

	private:
		unsigned int _freq;
		bool _running;
};

/*==============================================================================
 * ME_IntervalObserver
 *
 *     Interface used by the ME_Interval timer to provide the callback
 *     update() and draw() functions.
 *============================================================================*/
class ME_IntervalObserver
{
	public:
		virtual void update(ME_Interval*, double period) = 0;
		virtual void draw() = 0;
};

#endif
