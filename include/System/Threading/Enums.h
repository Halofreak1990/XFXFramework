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
		/// <summary>
		/// Indicates whether an System.Threading.EventWaitHandle is reset automatically or manually after receiving a
		/// signal.
		/// </summary>
		struct EventResetMode
		{
			enum type
			{
				AutoReset,
				ManualReset
			};
		};
		
		/// <summary>
		/// The System.Threading.Thread can be scheduled after threads with Highest priority and before those with
		/// Normal priority.
		/// </summary>
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

		typedef EventResetMode::type	EventResetMode_t;
		typedef ThreadPriority::type	ThreadPriority_t;
	}
}

#endif //_SYSTEM_THREADING_ENUMS_
