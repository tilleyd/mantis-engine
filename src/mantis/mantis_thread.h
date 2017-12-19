/*==============================================================================
 * Mantis Engine threading class headers
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

#ifndef ME_THREAD_H
#define ME_THREAD_H

#include <pthread.h>

/*==============================================================================
 * ME_Thread
 *
 *     Used for spawning a thread using the POSIX pthread library. The thread
 *     requires an object of type ME_Threadable to execute the threaded
 *     function.
 *============================================================================*/
class ME_Thread
{
	public:
		ME_Thread(ME_Threadable*);
		~ME_Thread();

		/*----------------------------------------------------------------------
		 * Starts the thread and executes the threadable function.            */
		void start();

		/*----------------------------------------------------------------------
		 * Joins the thread (i.e. waits for the threadable function to
		 * finish execution).                                                 */
		void join();

		static void* execute(void*);
	private:
		ME_Threadable* _threadable;
		pthread_t      _tid;
};

/*==============================================================================
 * ME_Threadable
 *
 *     The interface for threadable objects. Used with a ME_Thread object to
 *     spawn a thread that runs the execute() function.
 *============================================================================*/
class ME_Threadable
{
	public:
		virtual void execute() = 0;
};

#endif
