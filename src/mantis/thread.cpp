/*==============================================================================
 * ME_Thread implementation
 *     Author  : Duncan Tilley
 *     Modified: 2017 Oct 30
 *============================================================================*/

#include "mantis_thread.h"

#include <pthread.h>

ME_Thread::ME_Thread(ME_Threadable* thr)
	: _threadable(thr)
	, _tid(0)
{}

ME_Thread::~ME_Thread()
{
	join();
}

void ME_Thread::start()
{
	pthread_create(&_tid, NULL, ME_Thread::execute, (void*)_threadable);
}

void ME_Thread::join()
{
	pthread_join(_tid, NULL);
}

void* ME_Thread::execute(void* obj)
{
	ME_Threadable* thr = (ME_Threadable*)obj;
	thr->execute();
	return NULL;
}
