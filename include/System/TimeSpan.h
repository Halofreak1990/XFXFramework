/*****************************************************************************
 *	TimeSpan.h																 *
 *																			 *
 *	XFX System::TimeSpan definition file									 *
 *	Copyright (c) XFX Team. All Rights Reserved 							 *
 *****************************************************************************/
#ifndef _SYSTEM_TIMESPAN_
#define _SYSTEM_TIMESPAN_

#include "Interfaces.h"

namespace System
{
	// Represents a time interval.
	struct TimeSpan : IComparable<TimeSpan>, IEquatable<TimeSpan>, Object
	{
	private:
		long long _ticks;

		static bool CalculateTicks(int days, int hours, int minutes, int seconds, int milliseconds, bool throwExc, out long long result);
		static TimeSpan Interval(double value, int scale);
			
	public:
		static const TimeSpan MaxValue;
		static const TimeSpan MinValue;
		static const TimeSpan Zero;
		static const long long TicksPerMillisecond;
		static const long long TicksPerSecond;
		static const long long TicksPerMinute;
		static const long long TicksPerHour;
		static const long long TicksPerDay;
		
		int Days() const;
		int Hours() const;
		int Milliseconds() const;
		int Minutes() const;
		int Seconds() const;
		long long Ticks() const;
		double TotalDays() const;
		double TotalHours() const;
		double TotalMilliseconds() const;
		double TotalMinutes() const;
		double TotalSeconds() const;
			
		TimeSpan();
		TimeSpan(int hours, int minutes, int seconds);
		TimeSpan(int days, int hours, int minutes, int seconds);
		TimeSpan(int days, int hours, int minutes, int seconds, int milliseconds);
		TimeSpan(long long ticks);
		TimeSpan(const TimeSpan &obj);

		TimeSpan Add(const TimeSpan ts);
		static int Compare(const TimeSpan t1, const TimeSpan t2);
		int CompareTo(const TimeSpan ts) const;
		bool Equals(Object const * const obj) const;
		bool Equals(const TimeSpan obj) const;
		static bool Equals(const TimeSpan t1, const TimeSpan t2);
		static TimeSpan FromDays(double value);
		static TimeSpan FromHours(double value);
		static TimeSpan FromMilliseconds(double value);
		static TimeSpan FromMinutes(double value);
		static TimeSpan FromSeconds(double value);
		static TimeSpan FromTicks(long long value);
		int GetHashCode() const;
		static int GetType();
		TimeSpan Negate();
		TimeSpan Parse(const String& s); //! TODO
		TimeSpan Subtract(const TimeSpan ts);
		const String ToString() const; //! TODO

		TimeSpan operator +(const TimeSpan& other);
		bool operator==(const TimeSpan& other) const;
		bool operator >(const TimeSpan& other) const;
		bool operator>=(const TimeSpan& other) const;
		bool operator!=(const TimeSpan& other) const;
		bool operator <(const TimeSpan& other) const;
		bool operator<=(const TimeSpan& other) const;
		TimeSpan operator -(const TimeSpan& other);
		TimeSpan operator -();
	};
}

#endif //_SYSTEM_TIMESPAN_
