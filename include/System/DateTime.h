/********************************************************
 *	DateTime.h											*
 *														*
 *	XFX DateTime definition file						*
 *	Copyright © XFX Team. All Rights Reserved			*
 ********************************************************/
#ifndef _SYSTEM_DATETIME_
#define _SYSTEM_DATETIME_

#include "Globalization/Calendar.h"
#include "Globalization/Enums.h"
#include "Enums.h"
#include "Interfaces.h"
#include "Types.h"

using namespace System::Globalization;

namespace System
{
	class String;
	class TimeSpan;

	// Represents an instant in time, typically expressed as a date and time of day.
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
		DateTime Date() const;
		int Day() const;
		DayOfWeek_t DayOfWeek() const;
		int DayOfYear() const;
		int Hour() const;
		DateTimeKind_t Kind() const;
		int Millisecond() const;
		int Minute() const;
		int Month() const;
		static DateTime Now();
		int Second() const;
		Int64 Ticks() const;
		TimeSpan TimeOfDay() const;
		static DateTime Today();
		static DateTime UtcNow();
		int Year()const;
		static const DateTime MaxValue;
		static const DateTime MinValue;

		DateTime(int year, int month, int day);
		DateTime(int year, int month, int day, Calendar calendar);
		DateTime(int year, int month, int day, int hour, int minute, int second);
		DateTime(int year, int month, int day, int hour, int minute, int second, DateTimeKind_t kind);
		DateTime(int year, int month, int day, int hour, int minute, int second, Calendar calendar);
		DateTime(int year, int month, int day, int hour, int minute, int second, int millisecond);
		DateTime(int year, int month, int day, int hour, int minute, int second, int millisecond, DateTimeKind_t kind);
		DateTime(int year, int month, int day, int hour, int minute, int second, int millisecond, Calendar calendar);
		DateTime(int year, int month, int day, int hour, int minute, int second, int millisecond, Calendar calendar, DateTimeKind_t kind);
		DateTime(Int64 ticks);
		DateTime(Int64 ticks, DateTimeKind_t kind);
		DateTime(const DateTime &obj); //Copy constructor

		DateTime Add(const TimeSpan value);
		DateTime AddDays(double value);
		DateTime AddHours(double value);
		DateTime AddMilliseconds(double value);
		DateTime AddMinutes(double value);
		DateTime AddMonths(int months);
		DateTime AddSeconds(double value);
		DateTime AddTicks(Int64 value);
		DateTime AddYears(int value);
		static int Compare(const DateTime t1, const DateTime t2);
		int CompareTo(const DateTime value) const;
		static int DaysInMonth(int year, int month);
		bool Equals(const DateTime obj) const;
		bool static Equals(const DateTime t1, const DateTime t2);
		static DateTime FromFileTime(Int64 fileTime);
		static DateTime FromFileTimeUtc(Int64 fileTime);
		static DateTime FromOADate(double d);
		String *GetDateTimeFormats();
		String *GetDateTimeFormats(char format);
		String *GetDateTimeFormats(char format, IFormatProvider* formatProvider);
		String *GetDateTimeFormats(IFormatProvider* formatProvider);
		int GetHashCode() const;
		bool IsDaylighSavingTime();
		static bool IsLeapYear(int year);
		static DateTime Parse(String s);
		static DateTime Parse(String s, IFormatProvider &formatProvider);
		static DateTime Parse(String s, IFormatProvider &formatProvider, System::Globalization::DateTimeStyles_t styles);
		static DateTime ParseExact(String s, String format, IFormatProvider &formatProvider);
		static DateTime ParseExact(String s, String format, IFormatProvider &formatProvider, System::Globalization::DateTimeStyles_t style);
		static DateTime ParseExact(String s, String formats[], IFormatProvider &formatProvider, System::Globalization::DateTimeStyles_t style);
		static DateTime ParseExact(DateTime value, DateTimeKind kind);
		TimeSpan Subtract(const DateTime value);
		DateTime Subtract(const TimeSpan value);
		Int64 ToFileTime();
		Int64 ToFileTimeUtc();
		DateTime ToLocalTime();
		char* ToLongDateString();
		char* ToLongTimeString();
		double ToOADate();
		char* ToShortDateString();
		char* ToShortTimeString();
		char* ToString() const;
		char* ToString(IFormatProvider* provider);
		char* ToString(const char* format);
		char* ToString(const char* format, IFormatProvider* provider);
		DateTime ToUniversalTime();

		DateTime operator +(const TimeSpan other);
		bool operator==(const DateTime other) const;
		bool operator >(const DateTime other) const;
		bool operator>=(const DateTime other) const;
		bool operator!=(const DateTime other) const;
		bool operator <(const DateTime other) const;
		bool operator<=(const DateTime other) const;
		TimeSpan operator-(const DateTime other);
		DateTime operator-(const TimeSpan t);
	};
}

#endif //_DATETIME_
