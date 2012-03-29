/********************************************************
 *	EventArgs.h											*
 *														*
 *	XFX EventArgs class definition file					*
 *	Copyright © XFX Team. All Rights Reserved			*
 ********************************************************/
#ifndef _SYSTEM_EVENTARGS_
#define _SYSTEM_EVENTARGS_

#include "Object.h"

namespace System
{
	// EventArgs is the base class for classes containing event data.
	class EventArgs : virtual Object
	{
	public:
		static const EventArgs Empty;

		EventArgs()
		{
		}
	};
}

#endif //_SYSTEM_EVENTARGS_
