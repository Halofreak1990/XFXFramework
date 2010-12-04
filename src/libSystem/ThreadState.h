/********************************************************
 *	ThreadState.h										*
 *														*
 *	XFX ThreadState enumeration definition file			*
 *	Copyright © Halofreak1990. All Rights Reserved		*
 ********************************************************/
#ifndef THREADSTATE_H
#define THREADSTATE_H

namespace System
{
	namespace Threading
	{
		enum ThreadState
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
	}
}

#endif //THREADSTATE_H
