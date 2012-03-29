/********************************************************
 *	TimeSpan.h											*
 *														*
 *	XFX TimeSpan definition file						*
 *	Copyright © XFX Team. All Rights Reserved			*
 ********************************************************/
#ifndef _SYSTEM_TIMESPAN_
#define _SYSTEM_TIMESPAN_

#include "Interfaces.h"

namespace System
{
	// Represents a time interval.
	struct TimeSpan : public IComparable<TimeSpan>, public IEquatable<TimeSpan>, virtual Object
	{
	private:
		Int64 _ticks;

		static bool CalculateTicks(int days, int hours, int minutes, int seconds, int milliseconds, bool throwExc, out Int64 result);
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
		
		int Days() const;
		int Hours() const;
		int Milliseconds() const;
		int Minutes() const;
		int Seconds() const;
		Int64 Ticks() const;
		double TotalDays() const;
		double TotalHours() const;
		double TotalMilliseconds() const;
		double TotalMinutes() const;
		double TotalSeconds() const;
			
		TimeSpan();
		TimeSpan(int hours, int minutes, int seconds);
		TimeSpan(int days, int hours, int minutes, int seconds);
		TimeSpan(int days, int hours, int minutes, int seconds, int milliseconds);
		TimeSpan(Int64 ticks);
		TimeSpan(const TimeSpan &obj);

		TimeSpan Add(const TimeSpan ts);
		static int Compare(const TimeSpan t1, const TimeSpan t2);
		int CompareTo(const TimeSpan ts) const;
		bool Equals(const TimeSpan obj) const;
		static bool Equals(const TimeSpan t1, const TimeSpan t2);
		static TimeSpan FromDays(double value);
		static TimeSpan FromHours(double value);
		static TimeSpan FromMilliseconds(double value);
		static TimeSpan FromMinutes(double value);
		static TimeSpan FromSeconds(double value);
		static TimeSpan FromTicks(Int64 value);
		int GetHashCode() const;
		TimeSpan Negate();
		TimeSpan Parse(char* s); //! TODO
		TimeSpan Subtract(const TimeSpan ts);
		const char* ToString() const; //! TODO

		TimeSpan operator+(const TimeSpan other);
		bool operator==(const TimeSpan other) const;
		bool operator >(const TimeSpan other) const;
		bool operator>=(const TimeSpan other) const;
		bool operator!=(const TimeSpan other) const;
		bool operator <(const TimeSpan other) const;
		bool operator<=(const TimeSpan other) const;
		TimeSpan operator -(const TimeSpan other);
		TimeSpan operator -();
	};
}

#endif //_TIMESPAN_
