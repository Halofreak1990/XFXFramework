/********************************************************
 *	EventArgs.h											*
 *														*
 *	XFX EventArgs class definition file					*
 *	Copyright © XFX Team. All Rights Reserved			*
 ********************************************************/
#ifndef _SYSTEM_EVENTARGS_
#define _SYSTEM_EVENTARGS_

namespace System
{
	/// <summary>
	/// EventArgs is the base class for classes containing event data.
	/// </summary>
	class EventArgs
	{
	public:
		static const EventArgs Empty;

		EventArgs();
	};
}

#endif //_SYSTEM_EVENTARGS_
