/*****************************************************************************
 *	DateTime.h																 *
 *																			 *
 *	XFX System::DateTime structure definition file  						 *
 *	Copyright (c) XFX Team. All Rights Reserved 							 *
 *****************************************************************************/
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
	struct TimeSpan;

	/**
	 * Represents an instant in time, typically expressed as a date and time of day.
	 */
	struct DateTime : IComparable<DateTime>, IEquatable<DateTime>, Object
	{
	private:
		static const long long TicksMask;
		static const long long KindMask;
		static const int KindShift;
		static const long long w32file_epoch;
		static const long long MAX_VALUE_TICKS;
		static const long long UnixEpoch;
		long long encoded;
		int AbsoluteDays(int year, int month, int day);
		void InvalidTickValue(long long ticks);
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
		long long Ticks() const;
		TimeSpan TimeOfDay() const;
		static DateTime Today();
		static DateTime UtcNow();
		int Year() const;
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
		DateTime(long long ticks);
		DateTime(long long ticks, DateTimeKind_t kind);
		DateTime(const DateTime &obj); //Copy constructor

		DateTime Add(const TimeSpan value);
		DateTime AddDays(double value);
		DateTime AddHours(double value);
		DateTime AddMilliseconds(double value);
		DateTime AddMinutes(double value);
		DateTime AddMonths(int months);
		DateTime AddSeconds(double value);
		DateTime AddTicks(long long value);
		DateTime AddYears(int value);
		static int Compare(const DateTime t1, const DateTime t2);
		int CompareTo(const DateTime value) const;
		static int DaysInMonth(int year, int month);
		bool Equals(Object const * const obj) const;
		bool Equals(const DateTime obj) const;
		bool static Equals(const DateTime t1, const DateTime t2);
		static DateTime FromFileTime(long long fileTime);
		static DateTime FromFileTimeUtc(long long fileTime);
		static DateTime FromOADate(double d);
		String *GetDateTimeFormats();
		String *GetDateTimeFormats(char format);
		String *GetDateTimeFormats(char format, IFormatProvider * const formatProvider);
		String *GetDateTimeFormats(IFormatProvider * const formatProvider);
		int GetHashCode() const;
		static const Type& GetType();
		bool IsDaylighSavingTime();
		static bool IsLeapYear(int year);
		static DateTime Parse(String& s);
		static DateTime Parse(String& s, IFormatProvider * const formatProvider);
		static DateTime Parse(String& s, IFormatProvider * const formatProvider, DateTimeStyles_t styles);
		static DateTime ParseExact(String& s, String& format, IFormatProvider * const formatProvider);
		static DateTime ParseExact(String& s, String& format, IFormatProvider * const formatProvider, DateTimeStyles_t style);
		static DateTime ParseExact(String& s, String formats[], IFormatProvider * const formatProvider, DateTimeStyles_t style);
		static DateTime ParseExact(DateTime value, DateTimeKind kind);
		TimeSpan Subtract(const DateTime value);
		DateTime Subtract(const TimeSpan value);
		long long ToFileTime();
		long long ToFileTimeUtc();
		DateTime ToLocalTime();
		String ToLongDateString();
		String ToLongTimeString();
		double ToOADate();
		String ToShortDateString();
		String ToShortTimeString();
		const String ToString() const;
		String ToString(IFormatProvider * const provider);
		String ToString(const String& format);
		String ToString(const String& format, IFormatProvider * const provider);
		DateTime ToUniversalTime();

		DateTime operator +(const TimeSpan other);
		bool operator==(const DateTime& other) const;
		bool operator >(const DateTime other) const;
		bool operator>=(const DateTime other) const;
		bool operator!=(const DateTime& other) const;
		bool operator <(const DateTime other) const;
		bool operator<=(const DateTime other) const;
		TimeSpan operator-(const DateTime other);
		DateTime operator-(const TimeSpan t);
	};
}

#endif //_SYSTEM_DATETIME_
