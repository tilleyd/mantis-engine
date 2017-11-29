/*==============================================================================
 * Mantis Engine game loop class headers
 *============================================================================*/

#ifndef ME_LOOP_H
#define ME_LOOP_H

// forward declarations
class ME_Loop;
class ME_IntervalLoop;
class ME_UncappedLoop;
class ME_LoopObserver;

class ME_Graphics;

/*==============================================================================
 * ME_Loop
 *
 *     Abstract game loop timer that calls update() and draw() periodically. The
 *     loop class leaves the loop() template method for child loop classes.
 *============================================================================*/
class ME_Loop
{
	public:
		virtual ~ME_Loop() {}

		/*----------------------------------------------------------------------
		 * start() Starts the timer and periodically calls the update() and
		 * draw() methods on the provided ME_LoopObserver. Note that start()
		 * blocks and can only be stopped by calling stop().                  */
		void start(ME_LoopObserver*, ME_Graphics*);
		void stop();

	protected:
		/*----------------------------------------------------------------------
		 * Override this loop() method using the _running member to check for
		 * stop conditions.                                                   */
		virtual void loop() = 0;

		/*----------------------------------------------------------------------
		 * These should be used in the loop() method.                         */
		void draw();
		void update(double);

		bool _running;

	private:
		ME_LoopObserver* _observer;
		ME_Graphics*     _graphics;
};

/*==============================================================================
 * ME_IntervalLoop
 *
 *     Game loop that uses a capped FPS value to periodically call update() and
 *     draw(). This loop should be used in the absence of VSync and if an
 *     uncapped FPS is undesirable.
 *============================================================================*/
class ME_IntervalLoop : public ME_Loop
{
	public:
		/*----------------------------------------------------------------------
		 * Creates an interval loop with a provided FPS.                      */
		ME_IntervalLoop(unsigned int);

	protected:
		/*----------------------------------------------------------------------
		 * Override from ME_Loop                                              */
		void loop();

	private:
		unsigned int _fps;
};

/*==============================================================================
 * ME_UncappedLoop
 *
 *     Game loop that does not cap the FPS in any way, update() and draw() are
 *     called as frequently as possible. This loop is also used with VSync since
 *     no manual delays are necessary.
 *============================================================================*/
class ME_UncappedLoop : public ME_Loop
{
	protected:
		/*----------------------------------------------------------------------
		 * Override from ME_Loop                                              */
		void loop();
};

/*==============================================================================
 * ME_LoopObserver
 *
 *     Interface used by the ME_Loop timers to provide the callback update()
 *     and draw() functions.
 *============================================================================*/
class ME_LoopObserver
{
	public:
		virtual void update(ME_Loop*, double period) = 0;
		virtual void draw() = 0;
};

#include "mantis.h"

#endif
