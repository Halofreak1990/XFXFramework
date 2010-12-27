/********************************************************
 *	TimeSpan.h											*
 *														*
 *	XFX TimeSpan definition file						*
 *	Copyright © XFX Team. All Rights Reserved			*
 ********************************************************/
#ifndef _SYSTEM_TIMESPAN_
#define _SYSTEM_TIMESPAN_

#include "Types.h"

namespace System
{
	class TimeSpan
	{
	private:
		Int64 _ticks;

		static bool CalculateTicks(int days, int hours, int minutes, int seconds, int milliseconds, bool throwExc, out long long result);
		static TimeSpan Interval(double value, int scale);
			
	public:
		static const TimeSpan MaxValue;
		static const TimeSpan MinValue;
		static const TimeSpan Zero;
		static const Int64 TicksPerMillisecond;
		static const Int64 TicksPerSecond;
		static const Int64 TicksPerMinute;
		static const Int64 TicksPerHour;
		static const Int64 TicksPerDay;
		
		int Days();
		int Hours();
		int Milliseconds();
		int Minutes();
		int Seconds();
		Int64 Ticks();
		double TotalDays();
		double TotalHours();
		double TotalMilliseconds();
		double TotalMinutes();
		double TotalSeconds();
			
		TimeSpan();
		TimeSpan(int hours, int minutes, int seconds);
		TimeSpan(int days, int hours, int minutes, int seconds);
		TimeSpan(int days, int hours, int minutes, int seconds, int milliseconds);
		TimeSpan(long long ticks);
		TimeSpan(const TimeSpan &obj); // Copy constructor

		TimeSpan Add(TimeSpan ts);
		int Compare(TimeSpan t1, TimeSpan t2);
		int CompareTo(TimeSpan ts);
		bool Equals(TimeSpan obj);
		bool Equals(TimeSpan t1, TimeSpan t2);
		static TimeSpan FromDays(double value);
		static TimeSpan FromHours(double value);
		static TimeSpan FromMilliseconds(double value);
		static TimeSpan FromMinutes(double value);
		static TimeSpan FromSeconds(double value);
		static TimeSpan FromTicks(Int64 value);
		int GetHashCode();
		TimeSpan Negate();
		TimeSpan Parse(char* s); //! TODO
		TimeSpan Subtract(TimeSpan ts);
		char* ToString(); //! TODO

		TimeSpan operator+(const TimeSpan other);
		bool operator==(const TimeSpan other);
		bool operator >(const TimeSpan other);
		bool operator>=(const TimeSpan other);
		bool operator!=(const TimeSpan other);
		bool operator <(const TimeSpan other);
		bool operator<=(const TimeSpan other);
		TimeSpan operator -(const TimeSpan other);
		TimeSpan operator -();
	};
}

#endif //_TIMESPAN_
