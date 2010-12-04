/********************************************************
 *	TimeSpan.h											*
 *														*
 *	XFX TimeSpan definition file						*
 *	Copyright © XFX Team. All Rights Reserved			*
 ********************************************************/
#ifndef TIMESPAN_H
#define TIMESPAN_H

extern "C" {
#ifdef ENABLE_XBOX
#include <xboxkrnl/types.h>
#else
#include <types.h>
#endif
}

namespace System
{
	class TimeSpan
	{
			long _ticks;
			
		public:
			static const TimeSpan Zero;
			static const long TicksPerMillisecond;
			static const long TicksPerSecond;
			static const long TicksPerMinute;
			static const long long TicksPerHour;
			static const long long TicksPerDay;
			
			long Ticks();
			int Days();
			int Hours();
			int Milliseconds();
			int Minutes();
			int Seconds();
			
			TimeSpan(long ticks);
			TimeSpan(const TimeSpan &obj);
			TimeSpan();
			
			int operator!=(const TimeSpan &other);
			int operator==(const TimeSpan &other);
	};
}

#endif //TIMESPAN_H
