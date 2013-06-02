/********************************************************
 *	Thread.h											*
 *														*
 *	XFX Thread definition file							*
 *	Copyright (c) XFX Team. All Rights Reserved			*
 ********************************************************/
#ifndef _SYSTEM_THREADING_THREAD_
#define _SYSTEM_THREADING_THREAD_

extern "C"
{
#include <xboxkrnl/xboxkrnl.h>
}

#include "Enums.h"
#include "../TimeSpan.h"

namespace System
{
	namespace Threading
	{
		class Thread
		{
			int lock_thread_id;
			HANDLE system_thread_handle;
			PKSTART_ROUTINE callback;
			int stack_size;
			static ULONG Id;
			PULONG suspendCount;
			
			ThreadState_t state;
			
		private:
			void Thread_init();
			
		public:
			//Creates a new instance of the Thread class with the specified callback function, but doesn't start yet.
			Thread(PKSTART_ROUTINE callBack);
			//Creates a new instance of the Thread class with the specified callback function and stack size, but doesn't start yet.
			Thread(PKSTART_ROUTINE callBack, int stackSize);
			~Thread();
			
			void Abort();
			void Interrupt();
			//Returns a value indicating whether the thread is running
			bool IsAlive();
			//Resumes a previously suspended thread.
			void Resume();
			//Set the thread priority, valid values are 0 (Low), 16 (Low_RealTime), 31 (High), 32 (Maximum)
			void SetPriority(int priority);
			static void Sleep(int millisecondsTimeout);
			static void Sleep(TimeSpan timeout);
			//Start executing the thread.
			void Start();
			//Suspend the thread execution, call Thread::Resume() to resume the thread.
			void Suspend();
		};
	}
}

#endif //_SYSTEM_THREADING_THREAD_
