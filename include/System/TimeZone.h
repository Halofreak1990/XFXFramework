/********************************************************
 *	TimeZone.h											*
 *														*
 *	TimeZone definition file							*
 *	Copyright © XFX Team. All Rights Reserved			*
 ********************************************************/
#ifndef _SYSTEM_TIMEZONE_
#define _SYSTEM_TIMEZONE_

#include <System/Globalization/DaylightTime.h>

namespace System
{
	class DateTime;
	class String;
	class TimeSpan;

	/// <summary>
	/// Represents a time zone.
	/// </summary>
	class TimeZone
	{
	protected:
		TimeZone();

	public:
		static TimeZone CurrentTimeZone();
		String DaylightName();
		String StandardName();

		System::Globalization::DaylightTime GetDaylightChanges(int year);
		TimeSpan GetUtcOffset(DateTime time);
		bool IsDaylightSavingTime(DateTime time);
		static bool IsDaylightSavingTime(DateTime time, System::Globalization::DaylightTime daylightTimes);
		DateTime ToLocalTime(DateTime time);
		DateTime ToUniversalTime(DateTime time);
	};
}

#endif //_SYSTEM_TIMEZONE_
