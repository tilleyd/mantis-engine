/*==============================================================================
 * Mantis Engine game loop class headers
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
