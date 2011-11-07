/********************************************************
 *	Enums.h												*
 *														*
 *	System::Threading enumerations definition file		*
 *	Copyright © XFX Team. All Rights Reserved			*
 ********************************************************/
#ifndef _SYSTEM_THREADING_ENUMS_
#define _SYSTEM_THREADING_ENUMS_

namespace System
{
	namespace Threading
	{
		// Indicates whether an System::Threading::EventWaitHandle is reset automatically or manually after receiving a signal.
		struct EventResetMode
		{
			enum type
			{
				AutoReset,
				ManualReset
			};
		};
		
		// The System::Threading::Thread can be scheduled after threads with Highest priority and before those with Normal priority.
		struct ThreadPriority
		{
			enum type
			{
				AboveNormal,
				BelowNormal,
				Highest = 32,
				Lowest = 0,
				Normal,
			};
		};

		struct ThreadState
		{
			enum type
			{
				Running = 0x00000000,
				StopRequested = 0x00000001,
				SuspendRequested = 0x00000002,
				Background = 0x00000004,
	 			Unstarted = 0x00000008,
	 			Stopped = 0x00000010,
				WaitSleepJoin = 0x00000020,
				Suspended = 0x00000040,
				AbortRequested = 0x00000080,
				Aborted = 0x00000100
			};
		};

		typedef EventResetMode::type	EventResetMode_t;
		typedef ThreadPriority::type	ThreadPriority_t;
		typedef ThreadState::type		ThreadState_t;
	}
}

#endif //_SYSTEM_THREADING_ENUMS_
