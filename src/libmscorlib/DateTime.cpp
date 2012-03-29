// Copyright (C) 2010-2012, XFX Team
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

#include <stdio.h>

#include <System/DateTime.h>
#include <System/Math.h>
#include <System/String.h>
#include <System/String.h>
#include <System/TimeSpan.h>
#include <System/TimeZone.h>

#include <sassert.h>

namespace System
{
	// Encodes the DateTime in 64 bits, top two bits contain the DateTimeKind,
	// the rest contains the 62 bit value for the ticks.   This reduces the
	// memory usage from 16 to 8 bytes.
	//
	const Int64 DateTime::TicksMask = 0x3fffffffffffffffLL;
	const Int64 DateTime::KindMask = ((Int64)0xc000000000000000LL);
	const int DateTime::KindShift = 62;
	//
	// w32 file time starts counting from 1/1/1601 00:00 GMT
	// which is the constant ticks from the .NET epoch
	const Int64 DateTime::w32file_epoch = 504911232000000000LL;
	//
	//private const long MAX_VALUE_TICKS = 3155378975400000000L;
	// -- Microsoft .NET has this value.
	const Int64 DateTime::MAX_VALUE_TICKS = 3155378975999999999LL;
	//
	// The UnixEpoch, it begins on Jan 1, 1970 at 0:0:0, expressed
	// in Ticks
	//
	const Int64 DateTime::UnixEpoch = 621355968000000000LL;

	// for OLE Automation dates
	Int64 ticks18991230 = 599264352000000000LL;
	double OAMinValue = -657435.0;
	double OAMaxValue = 2958466.0;

	int daysmonth[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };	
	int daysmonthleap[] = { 0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

	int DateTime::AbsoluteDays(int year, int month, int day)
	{
		int *days;
		int temp = 0, m=1 ;
	
		days = (IsLeapYear(year) ? daysmonthleap  : daysmonth);
			
		while (m < month)
			temp += days[m++];
		return ((day-1) + temp + (365* (year-1)) + ((year-1)/4) - ((year-1)/100) + ((year-1)/400));
	}

	const DateTime DateTime::MaxValue = DateTime(3155378975999999999LL);
	const DateTime DateTime::MinValue = DateTime(0);

	void DateTime::InvalidTickValue(Int64 ticks)
	{
#if DEBUG
		//throw ArgumentOutOfRangeException("ticks", String::Format("Value %d is outside the valid range [0,%d].", ticks, MAX_VALUE_TICKS));
#endif
	}

	DateTime DateTime::Add(double value, int scale)
	{
		Int64 num = (Int64) ((value * scale) + ((value >= 0.0) ? 0.5 : -0.5));
        if ((num <= -315537897600000LL) || (num >= 0x11efae44cb400LL))
		{
#if DEBUG
            //throw ArgumentOutOfRangeException("value", "ArgumentOutOfRange_AddValue");
#endif
			return *this;
		}

        return AddTicks(num * 0x2710L);
	}

	DateTime::DateTime(int year, int month, int day)
	{
		DateTime(year, month, day, 0, 0, 0, 0);
	}

	DateTime::DateTime(int year, int month, int day, System::Globalization::Calendar calendar)
	{
		DateTime(year, month, day, 0, 0, 0, 0, calendar);
	}

	DateTime::DateTime(int year, int month, int day, int hour, int minute, int second)
	{
		DateTime(year, month, day, hour, minute, second, 0);
	}

	DateTime::DateTime(int year, int month, int day, int hour, int minute, int second, int millisecond)
	{
		sassert(!(year < 1 || year > 9999 || month < 1 || month >12  ||
			day < 1 || day > DaysInMonth(year, month) || hour < 0 || hour > 23 ||
			minute < 0 || minute > 59 || second < 0 || second > 59 ||
			millisecond < 0 || millisecond > 999), "Parameters describe an unrepresentable DateTime.");

		encoded = TimeSpan(AbsoluteDays(year,month,day), hour, minute, second, millisecond).Ticks();
	}

	DateTime::DateTime(Int64 ticks)
	{
		if (ticks < 0 || ticks > MAX_VALUE_TICKS)
			InvalidTickValue(ticks);
		encoded = ticks;
	}

	DateTime::DateTime(Int64 ticks, DateTimeKind_t kind)
	{
		if (ticks < 0 || ticks > MAX_VALUE_TICKS)
			InvalidTickValue(ticks);
		sassert(!(kind < 0 || kind > DateTimeKind::Local), "kind is an invalid DateTimeKind value.");

		encoded = ((Int64)kind << KindShift) | ticks;
	}

	DateTime::DateTime(const DateTime &obj)
	{
		encoded = obj.encoded;
	}

	DateTime DateTime::AddDays(double value)
	{
		return Add(value, 0x5265c00);
	}

	DateTime DateTime::AddHours(double value)
	{
		return Add(value, 0x36ee80);
	}

	DateTime DateTime::AddMilliseconds(double value)
	{
		return Add(value, 1);
	}

	DateTime DateTime::AddMinutes(double value)
	{
		return Add(value, 0xea60);
	}

	DateTime DateTime::AddMonths(int months)
	{
		int day, month, year,  maxday;

		day = Day();
		month = Month() + (months % 12);
		year = Year() + months/12;
			
		if (month < 1)
		{
			month = 12 + month;
			year--;
		}
		else if (month > 12) 
		{
			month = month -12;
			year++;
		}
		maxday = DaysInMonth(year, month);
		if (day > maxday)
			day = maxday;

		DateTime temp = DateTime(year, month, day);
		temp.encoded |= encoded & KindMask;
		return temp.Add(TimeOfDay());
	}

	DateTime DateTime::AddSeconds(double value)
	{
		return Add(value, 0x3e8);
	}

	DateTime DateTime::AddYears(int value)
	{
		return AddMonths(value * 12);
	}

	int DateTime::Compare(const DateTime t1, const DateTime t2)
	{
		Int64 t1t = t1.encoded & TicksMask;
		Int64 t2t = t2.encoded & TicksMask;

		if (t1t < t2t)
			return -1;
		else if (t1t > t2t)
			return 1;
		else
			return 0;
	}

	int DateTime::CompareTo(const DateTime value) const
	{
		return Compare(*this, value);
	}

	int DateTime::DaysInMonth(int year, int month)
	{
		int *days;

		sassert(!(month < 1 || month > 12), "month must be greater than 0 and smaller than, or equal to 12.");

		sassert(!(year < 1 || year > 9999), "year must be greater than 0 and smaller than, or equal to 9999.");

		days = (IsLeapYear(year) ? daysmonthleap  : daysmonth);
		return days[month];
	}

	bool DateTime::Equals(const DateTime obj) const
	{
		return (encoded & TicksMask) == (obj.encoded & TicksMask);
	}

	DateTime DateTime::FromFileTime(Int64 fileTime)
	{
		sassert(fileTime >= 0, "fileTime must be non-negative.");

		return DateTime(w32file_epoch + fileTime).ToLocalTime();
	}

	DateTime DateTime::FromFileTimeUtc(Int64 fileTime)
	{
		sassert(fileTime >= 0, "fileTime must be non-negative.");

		return DateTime(w32file_epoch + fileTime);
	}

	DateTime DateTime::FromOADate(double d)
	{
		// An OLE Automation date is implemented as a floating-point number
		// whose value is the number of days from midnight, 30 December 1899.

		// d must be negative 657435.0 through positive 2958466.0.
		sassert(!((d <= OAMinValue) || (d >= OAMaxValue)), "");

		DateTime dt = DateTime(ticks18991230);
		if (d < 0.0) {
			double days = Math::Ceiling(d);
			// integer part is the number of days (negative)
			dt = dt.AddMilliseconds(days * 86400000);
			// but decimals are the number of hours (in days fractions) and positive
			double hours = (days - d);
			dt = dt.AddMilliseconds(hours * 86400000);
		}
		else {
			dt = dt.AddMilliseconds(d * 86400000);
		}

		return dt;
	}

	int DateTime::GetHashCode() const
	{
		return (int)encoded;
	}

	bool DateTime::IsDaylighSavingTime()
	{
		if ((int)((ulong)encoded >> KindShift) == (int)DateTimeKind::Utc)
			return false;
		return TimeZone::CurrentTimeZone().IsDaylightSavingTime(*this);
	}

	bool DateTime::IsLeapYear(int year)
	{
		sassert(!(year < 1 || year > 9999), "year must be greater than 0 and smaller than, or equal to 9999.");

		return ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0);
	}

	TimeSpan DateTime::Subtract(const DateTime value)
	{
		return TimeSpan(Ticks()) - TimeSpan(value.Ticks());
	}

	DateTime DateTime::Subtract(const TimeSpan value)
	{
		Int64 newticks;

		newticks = Ticks() - value.Ticks();
		sassert(!(newticks < 0 || newticks > MAX_VALUE_TICKS), "argument out of range.");

		DateTime ret = DateTime(newticks);
		ret.encoded |= (encoded & KindMask);
		return ret;
	}

	Int64 DateTime::ToFileTime()
	{
		DateTime universalTime = ToUniversalTime();
			
		sassert(universalTime.Ticks() >= w32file_epoch, "file time is not valid.");
			
		return(universalTime.Ticks() - w32file_epoch);
	}

	Int64 DateTime::ToFileTimeUtc()
	{
		sassert(Ticks() >= w32file_epoch, "file time is not valid.");

		return (Ticks() - w32file_epoch);
	}

	double DateTime::ToOADate()
	{
		Int64 t = Ticks();
		// uninitialized DateTime case
		if (t == 0)
			return 0;
		// we can't reach minimum value
		if (t < 31242239136000000LL)
			return OAMinValue + 0.001;

		TimeSpan ts = TimeSpan(Ticks() - ticks18991230);
		double result = ts.TotalDays();
		// t < 0 (where 599264352000000000 == 0.0d for OA)
		if (t < 599264352000000000LL)
		{
			// negative days (int) but decimals are positive
			double d = Math::Ceiling(result);
			result = d - 2 - (result - d);
		}
		else
		{
			// we can't reach maximum value
			if (result >= OAMaxValue)
				result = OAMaxValue - 0.00000001;
		}
		return result;
	}

	DateTime DateTime::operator +(TimeSpan other)
	{
		Int64 res = ((encoded & TicksMask) + other.Ticks());
		if (res < 0 || res > MAX_VALUE_TICKS)
		{
#if DEBUG
			//throw new ArgumentOutOfRangeException();
#endif
			return DateTime(0);
		}
				
		return DateTime(res, Kind());
	}

	bool DateTime::operator==(const DateTime other) const
	{
		return Equals(other);
	}

	bool DateTime::operator >(const DateTime other) const
	{
		return ((encoded & TicksMask) > (other.encoded & TicksMask));
	}

	bool DateTime::operator>=(const DateTime other) const
	{
		return ((encoded & TicksMask) >= (other.encoded & TicksMask));
	}

	bool DateTime::operator!=(const DateTime other) const
	{
		return !Equals(other);
	}

	bool DateTime::operator <(const DateTime other) const
	{
		return ((encoded & TicksMask) < (other.encoded & TicksMask));
	}

	bool DateTime::operator<=(const DateTime other) const
	{
		return ((encoded & TicksMask) <= (other.encoded & TicksMask));
	}

	TimeSpan DateTime::operator -(DateTime other)
	{
		return TimeSpan((encoded & TicksMask) - (other.encoded & TicksMask));
	}

	DateTime DateTime::operator -(TimeSpan t)
	{
		Int64 res = ((encoded & TicksMask) - t.Ticks());
		if (res < 0 || res > MAX_VALUE_TICKS)
		{
#if DEBUG
			//throw ArgumentOutOfRangeException();
#endif
			return DateTime(0);
		}
		return DateTime(res, Kind());
	}
}
