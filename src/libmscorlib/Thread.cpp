// Copyright (C) XFX Team
// All rights reserved.
// 
// Redistribution and use in source and binary forms, with or without 
// modification, are permitted provided that the following conditions are met:
// 
//* Redistributions of source code must retain the above copyright 
//notice, this list of conditions and the following disclaimer.
//* Redistributions in binary form must reproduce the above copyright 
//notice, this list of conditions and the following disclaimer in the 
//documentation and/or other materials provided with the distribution.
//* Neither the name of the copyright holder nor the names of any 
//contributors may be used to endorse or promote products derived from 
//this software without specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE 
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE 
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR 
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF 
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS 
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN 
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE 
// POSSIBILITY OF SUCH DAMAGE.

#include <System/Threading/Thread.h>

namespace System
{
	namespace Threading
	{
		ULONG Thread::GlobalId = 0;

		void Thread::Thread_init()
		{
			PsCreateSystemThreadEx(&system_thread_handle,	// Thread Handle
													   0,	// KernelStackSize
											  stack_size,	// Stack Size
													   0,	// TlsDataSize
													 &Id,	// Thread ID
													NULL,	// StartContext1
													NULL,	// StartContext2
													TRUE,	// CreateSuspended
												   FALSE,	// DebugStack
							(PKSTART_ROUTINE)&callback);	// StartRoutine

			ObReferenceObjectByHandle(system_thread_handle, (POBJECT_TYPE)PsThreadObjectType, &system_thread_handle);

			//#define LOW_PRIORITY                      0
			//#define LOW_REALTIME_PRIORITY             16
			//#define HIGH_PRIORITY                     31
			//#define MAXIMUM_PRIORITY                  32

			KeSetBasePriorityThread((PKTHREAD)system_thread_handle, (PVOID)0); //Default the thread to low priority

			state = ThreadState::Unstarted;

			Id = GlobalId++; //increment Id so every thread Id is unique
		}
		
		void Thread::Abort()
		{
			PsTerminateSystemThread(STATUS_SUCCESS);
			state = ThreadState::Aborted;
		}
		
		Thread::Thread(PKSTART_ROUTINE callBack)
		{
			stack_size = 65536;
			callback = callBack;
			Thread_init();
		}
		
		Thread::Thread(PKSTART_ROUTINE callBack, int stackSize)
		{
			if(stackSize < 131072)
			{
				stack_size = 65536; //Default stack size is 65536, which should be enough, unless there is need for a > 128k stack.
			}

			stack_size = stackSize;
			callback = callBack;
			Thread_init();
		}
		
		void Thread::Resume()
		{
			NtResumeThread(&system_thread_handle, suspendCount);
			state = ThreadState::Running;
		}
		
		void Thread::SetPriority(int priority)
		{
			if ((priority != 0) && (priority != 16) && (priority != 31) && (priority != 32))
			{
				return; //no valid values
			}

			ObReferenceObjectByHandle(system_thread_handle, (POBJECT_TYPE)PsThreadObjectType, &system_thread_handle);
			KeSetBasePriorityThread((PKTHREAD)system_thread_handle, (PVOID)priority);
		}
		
		void Thread::Sleep(int millisecondsTimeout)
		{
			if (millisecondsTimeout <= 0)
			{
				return; //no reason to sleep. We could also throw an ArgumentOutOfRangeException, but what's the point in that?
			}

			LARGE_INTEGER pli;

			pli.QuadPart = -(millisecondsTimeout * 10000);

			KeDelayExecutionThread((KPROCESSOR_MODE)0, FALSE, &pli);
		}
		
		void Thread::Sleep(TimeSpan timeout)
		{
			if(timeout == TimeSpan::Zero)
			{
				return; //! no reason to sleep
			}

			LARGE_INTEGER pli;

			pli.QuadPart = -timeout.Ticks();
			KeDelayExecutionThread((KPROCESSOR_MODE)0, FALSE, &pli);
		}
		
		void Thread::Start()
		{
			Resume();
		}
		
		void Thread::Suspend()
		{
			NtSuspendThread(&system_thread_handle, suspendCount);
			state = ThreadState::Suspended;
		}
		
		bool Thread::IsAlive()
		{
			return !((state == ThreadState::Aborted) || (state == ThreadState::Stopped) || (state == ThreadState::Unstarted));
		}

		Thread::~Thread()
		{
			//! Remove any otherwise persistent references to this instance
			ObfDereferenceObject(system_thread_handle);
		}
	}
}
