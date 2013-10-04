// Copyright (C) XFX Team
// All rights reserved.
// 
// Redistribution and use in source and binary forms, with or without 
// modification, are permitted provided that the following conditions are met:
// 
//* Redistributions of source code must retain the above copyright 
//notice, this list of conditions and the following disclaimer.
//* Redistributions in binary form must reproduce the above copyright 
//notice, this list of conditions and the following disclaimer in the 
//documentation and/or other materials provided with the distribution.
//* Neither the name of the copyright holder nor the names of any 
//contributors may be used to endorse or promote products derived from 
//this software without specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE 
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE 
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR 
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF 
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS 
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN 
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE 
// POSSIBILITY OF SUCH DAMAGE.

#include <System/String.h>
#include <System/TimeSpan.h>
#include <System/Type.h>

#include <sassert.h>

namespace System
{
	const TimeSpan TimeSpan::Zero = TimeSpan(0L);
	const TimeSpan TimeSpan::MaxValue = TimeSpan(0x7fffffffffffffffLL);
	const TimeSpan TimeSpan::MinValue = TimeSpan(-9223372036854775808LL);
	const long long TimeSpan::TicksPerMillisecond = 10000L;
	const long long TimeSpan::TicksPerSecond = 10000000L;
	const long long TimeSpan::TicksPerMinute = 600000000L;
	const long long TimeSpan::TicksPerHour = 36000000000LL;
	const long long TimeSpan::TicksPerDay = 864000000000LL;

	const Type TimeSpanTypeInfo("TimeSpan", "System::TimeSpan", TypeCode::Object);

	TimeSpan::TimeSpan()
	{
		_ticks = 0;
	}

	TimeSpan::TimeSpan(int hours, int minutes, int seconds)
	{
		CalculateTicks(0, hours, minutes, seconds, 0, true, _ticks);
	}

	TimeSpan::TimeSpan(int days, int hours, int minutes, int seconds)
	{
		CalculateTicks(days, hours, minutes, seconds, 0, true, _ticks);
	}

	TimeSpan::TimeSpan(int days, int hours, int minutes, int seconds, int milliseconds)
	{
		CalculateTicks(days, hours, minutes, seconds, milliseconds, true, _ticks);
	}
	
	TimeSpan::TimeSpan(long long ticks)
	{
		_ticks = ticks;
	}

	TimeSpan::TimeSpan(const TimeSpan &obj)
	{
		_ticks = obj._ticks;
	}

	int TimeSpan::Days() const
	{
		return (int) (_ticks / TicksPerDay);
	}
	
	int TimeSpan::Hours() const
	{
		return (int) (_ticks % TicksPerDay / TicksPerHour);
	}
	
	int TimeSpan::Milliseconds() const
	{
		return (int) (_ticks % TicksPerSecond / TicksPerMillisecond);
	}
	
	int TimeSpan::Minutes() const
	{
		return (int) (_ticks % TicksPerHour / TicksPerMinute);
	}
	
	int TimeSpan::Seconds() const
	{
		return (int) (_ticks % TicksPerMinute / TicksPerSecond);
	}

	long long TimeSpan::Ticks() const
	{
		return _ticks;
	}

	double TimeSpan::TotalDays() const
	{
		return (double) _ticks / TicksPerDay;
	}

	double TimeSpan::TotalHours() const
	{
		return (double) _ticks / TicksPerHour;
	}

	double TimeSpan::TotalMilliseconds() const
	{
		return (double) _ticks  / TicksPerMillisecond;
	}

	double TimeSpan::TotalMinutes() const
	{
		return (double) _ticks / TicksPerMinute;
	}

	double TimeSpan::TotalSeconds() const
	{
		return (double) _ticks / TicksPerSecond;
	}

	TimeSpan TimeSpan::Add(const TimeSpan ts)
	{
		long long temp;
		temp = _ticks + ts._ticks;

		//! Check for overflow
		sassert(!(temp - ts._ticks != _ticks), "Resulting TimeSpan is too big.");

		//! Everything checks out
		return TimeSpan(_ticks + ts._ticks);
	}

	int TimeSpan::Compare(const TimeSpan t1, const TimeSpan t2)
	{
		if (t1._ticks < t2._ticks)
		{
			return -1;
		}

		if (t1._ticks > t2._ticks)
		{
			return 1;
		}

		return 0;
	}

	int TimeSpan::CompareTo(const TimeSpan ts) const
	{
		return Compare(*this, ts);
	}

	bool TimeSpan::Equals(Object const * const obj) const
	{
		return is(obj, this) ? *this == *(TimeSpan*)obj : false;
	}

	bool TimeSpan::Equals(const TimeSpan obj) const
	{
		return (_ticks == obj._ticks);
	}

	bool TimeSpan::Equals(const TimeSpan t1, const TimeSpan t2)
	{
		return t1.Equals(t2);
	}

	TimeSpan TimeSpan::FromDays(double value)
	{
		return Interval(value, 0x5265c00);
	}

	TimeSpan TimeSpan::FromHours(double value)
	{
		return Interval(value, 0x36ee80);
	}

	TimeSpan TimeSpan::FromMilliseconds(double value)
	{
		return Interval(value, 1);
	}

	TimeSpan TimeSpan::FromMinutes(double value)
	{
		return Interval(value, 0xea60);
	}

	TimeSpan TimeSpan::FromSeconds(double value)
	{
		return Interval(value, 0x3e8);
	}

	TimeSpan TimeSpan::FromTicks(long long value)
	{
		return TimeSpan(value);
	}

	int TimeSpan::GetHashCode() const
	{
		return (((int)_ticks) ^ ((int)(_ticks >> 0x20)));
	}

	const Type& TimeSpan::GetType()
	{
		return TimeSpanTypeInfo;
	}

	TimeSpan TimeSpan::Negate()
	{
		sassert(_ticks != MinValue._ticks, "");

		return TimeSpan(-_ticks);
	}

	TimeSpan TimeSpan::Subtract(const TimeSpan ts)
	{
		long long ticks = _ticks - ts._ticks;

		sassert(!(((_ticks >> 0x3f) != (ts._ticks >> 0x3f)) && ((_ticks >> 0x3f) != (ticks >> 0x3f))), "TimeSpan too long.");

		return TimeSpan(ticks);
	}

	const String TimeSpan::ToString() const
	{
		return String::Format("Ticks: %ll", _ticks);
	}

	TimeSpan TimeSpan::operator +(const TimeSpan& other)
	{
		return Add(other);
	}

	bool TimeSpan::operator==(const TimeSpan& other) const
	{
		return Equals(other);
	}

	bool TimeSpan::operator >(const TimeSpan& other) const
	{
		return _ticks > other._ticks;
	}

	bool TimeSpan::operator >=(const TimeSpan& other) const
	{
		return _ticks >= other._ticks;
	}
	
	bool TimeSpan::operator!=(const TimeSpan& other) const
	{
		return !Equals(other);
	}

	bool TimeSpan::operator <(const TimeSpan& other) const
	{
		return _ticks < other._ticks;
	}

	bool TimeSpan::operator <=(const TimeSpan& other) const
	{
		return _ticks <= other._ticks;
	}

	TimeSpan TimeSpan::operator -(const TimeSpan& other)
	{
		return Subtract(other);
	}

	TimeSpan TimeSpan::operator -()
	{
		return Negate();
	}

	bool TimeSpan::CalculateTicks(int days, int hours, int minutes, int seconds, int milliseconds, bool throwExc, long long result)
	{
		// there's no overflow checks for hours, minutes, ...
		// so big hours/minutes values can overflow at some point and change expected values
		int hrssec = (hours * 3600); // break point at (Int32.MaxValue - 596523)
		int minsec = (minutes * 60);
		long long t = ((long long)(hrssec + minsec + seconds) * 1000L + (long long)milliseconds);
		t *= 10000;

		result = 0;

		bool overflow = false;
		// days is problematic because it can overflow but that overflow can be 
		// "legal" (i.e. temporary) (e.g. if other parameters are negative) or 
		// illegal (e.g. sign change).
		if (days > 0) {
			long long td = TicksPerDay * days;
			if (t < 0) {
				long long ticks = t;
				t += td;
				// positive days -> total ticks should be lower
				overflow = (ticks > t);
			}
			else {
				t += td;
				// positive + positive != negative result
				overflow = (t < 0);
			}
		}
		else if (days < 0) {
			long long td = TicksPerDay * days;
			if (t <= 0) {
				t += td;
				// negative + negative != positive result
				overflow = (t > 0);
			}
			else {
				long long ticks = t;
				t += td;
				// negative days -> total ticks should be lower
				overflow = (t > ticks);
			}
		}

		if (overflow)
		{
			sassert(!throwExc, "The timespan is too big or too small.");

			return false;
		}

		result = t;
		return true;
	}

	TimeSpan TimeSpan::Interval(double value, int scale)
	{
		double num = value * scale;
		double num2 = num + ((value >= 0.0) ? 0.5 : -0.5);

		sassert(!((num2 > 922337203685477LL) || (num2 < -922337203685477LL)), "TimeSpan too long.");

		return TimeSpan(((long long)num2) * 0x2710L);
	}
}
