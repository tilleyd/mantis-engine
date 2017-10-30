/*==============================================================================
 * Mantis Engine threading class headers
 *     Author  : Duncan Tilley
 *     Modified: 2017 Oct 30
 *============================================================================*/

#ifndef ME_THREAD_H
#define ME_THREAD_H

#include <pthread.h>

// forward declarations
class ME_Thread;
class ME_Threadable;

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

		/*----------------------------------------------------------------------
		 * Starts the thread and executes the threadable function.            */
		void start();

		/*----------------------------------------------------------------------
		 * Joins the thread (i.e. waits for the threadable function to
		 * finish execution.                                                  */
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
