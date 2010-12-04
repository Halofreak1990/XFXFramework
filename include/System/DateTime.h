/********************************************************
 *	DateTime.h											*
 *														*
 *	XFX DateTime definition file						*
 *	Copyright © XFX Team. All Rights Reserved			*
 ********************************************************/
#ifndef _DATETIME_
#define _DATETIME_

#include "Globalization/Calendar.h"
#include "Globalization/Enums.h"
#include "Enums.h"
#include "Interfaces.h"
#include "Types.h"

namespace System
{
	class String;
	class TimeSpan;

	/// <summary>
	/// Represents an instant in time, typically expressed as a date and time of day.
	/// </summary>
	class DateTime
	{
	private:
		static const Int64 TicksMask;
		static const Int64 KindMask;
		static const int KindShift;
		static const Int64 w32file_epoch;
		static const Int64 MAX_VALUE_TICKS;
		static const Int64 UnixEpoch;
		Int64 encoded;
		int AbsoluteDays(int year, int month, int day);
		void InvalidTickValue(Int64 ticks);
		DateTime Add(double value, int scale);

	public:
		DateTime Date();
		int Day();
		DayOfWeek_t DayOfWeek();
		int DayOfYear();
		int Hour();
		DateTimeKind_t Kind();
		int Millisecond();
		int Minute();
		int Month();
		static DateTime Now();
		int Second();
		Int64 Ticks();
		TimeSpan TimeOfDay();
		static DateTime Today();
		static DateTime UtcNow();
		int Year();
		static const DateTime MaxValue;
		static const DateTime MinValue;

		DateTime(int year, int month, int day);
		DateTime(int year, int month, int day, System::Globalization::Calendar calendar);
		DateTime(int year, int month, int day, int hour, int minute, int second);
		DateTime(int year, int month, int day, int hour, int minute, int second, DateTimeKind_t kind);
		DateTime(int year, int month, int day, int hour, int minute, int second, System::Globalization::Calendar calendar);
		DateTime(int year, int month, int day, int hour, int minute, int second, int millisecond);
		DateTime(int year, int month, int day, int hour, int minute, int second, int millisecond, DateTimeKind_t kind);
		DateTime(int year, int month, int day, int hour, int minute, int second, int millisecond, System::Globalization::Calendar calendar);
		DateTime(int year, int month, int day, int hour, int minute, int second, int millisecond, System::Globalization::Calendar calendar, DateTimeKind_t kind);
		DateTime(Int64 ticks);
		DateTime(Int64 ticks, DateTimeKind_t kind);
		DateTime(const DateTime &obj); //Copy constructor

		DateTime Add(TimeSpan value);
		DateTime AddDays(double value);
		DateTime AddHours(double value);
		DateTime AddMilliseconds(double value);
		DateTime AddMinutes(double value);
		DateTime AddMonths(int months);
		DateTime AddSeconds(double value);
		DateTime AddTicks(Int64 value);
		DateTime AddYears(int value);
		static int Compare(DateTime t1, DateTime t2);
		int CompareTo(DateTime value);
		static int DaysInMonth(int year, int month);
		bool Equals(DateTime obj);
		bool static Equals(DateTime t1, DateTime t2);
		static DateTime FromFileTime(Int64 fileTime);
		static DateTime FromFileTimeUtc(Int64 fileTime);
		static DateTime FromOADate(double d);
		String *GetDateTimeFormats();
		String *GetDateTimeFormats(char format);
		String *GetDateTimeFormats(char format, IFormatProvider &formatProvider);
		String *GetDateTimeFormats(IFormatProvider &formatProvider);
		int GetHashCode();
		bool IsDaylighSavingTime();
		static bool IsLeapYear(int year);
		static DateTime Parse(String s);
		static DateTime Parse(String s, IFormatProvider &formatProvider);
		static DateTime Parse(String s, IFormatProvider &formatProvider, System::Globalization::DateTimeStyles_t styles);
		static DateTime ParseExact(String s, String format, IFormatProvider &formatProvider);
		static DateTime ParseExact(String s, String format, IFormatProvider &formatProvider, System::Globalization::DateTimeStyles_t style);
		static DateTime ParseExact(String s, String formats[], IFormatProvider &formatProvider, System::Globalization::DateTimeStyles_t style);
		static DateTime ParseExact(DateTime value, DateTimeKind kind);
		TimeSpan Subtract(DateTime value);
		DateTime Subtract(TimeSpan value);
		Int64 ToFileTime();
		Int64 ToFileTimeUtc();
		DateTime ToLocalTime();
		String ToLongDateString();
		String ToLongTimeString();
		double ToOADate();
		String ToShortDateString();
		String ToShortTimeString();
		String ToString();
		String ToString(IFormatProvider &provider);
		String ToString(String format);
		String ToString(String format, IFormatProvider &provider);
		DateTime ToUniversalTime();

		DateTime operator +(const TimeSpan other);
		bool operator==(const DateTime other);
		bool operator >(const DateTime other);
		bool operator>=(const DateTime other);
		bool operator!=(const DateTime other);
		bool operator <(const DateTime other);
		bool operator<=(const DateTime other);
		TimeSpan operator-(const DateTime other);
		DateTime operator-(const TimeSpan t);
	};
}

#endif //_DATETIME_
