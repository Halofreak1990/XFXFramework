/*****************************************************************************
 *	TimeZone.h																 *
 *																			 *
 *	System::TimeZone definition file										 *
 *	Copyright (c) XFX Team. All Rights Reserved 							 *
 *****************************************************************************/
#ifndef _SYSTEM_TIMEZONE_
#define _SYSTEM_TIMEZONE_

#include <System/Object.h>
#include <System/Globalization/DaylightTime.h>

using namespace System::Globalization;

namespace System
{
	struct DateTime;
	class String;
	struct TimeSpan;

	// Represents a time zone.
	class TimeZone : public Object
	{
	protected:
		TimeZone();

	public:
		static TimeZone CurrentTimeZone();
		String DaylightName();
		String StandardName();

		DaylightTime GetDaylightChanges(int year);
		int GetType() const;
		TimeSpan GetUtcOffset(DateTime time);
		bool IsDaylightSavingTime(DateTime time);
		static bool IsDaylightSavingTime(DateTime time, DaylightTime daylightTimes);
		DateTime ToLocalTime(DateTime time);
		DateTime ToUniversalTime(DateTime time);
	};
}

#endif //_SYSTEM_TIMEZONE_
