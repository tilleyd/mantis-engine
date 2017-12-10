/*==============================================================================
 * ME_Thread implementation
 *==============================================================================
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
