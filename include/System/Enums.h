/****************************************************************
 *	Enums.h														*
 *		Defines enumerations used in the System namespace		*
 *																*
 *		Enumerations are defined inside structs to prevent		*
 *		namespace pollution, and easier distinction.			*
 ****************************************************************/
#ifndef _SYSTEM_ENUMS_
#define _SYSTEM_ENUMS_

namespace System
{
	// Specifies whether a System::DateTime object represents a local time, a Coordinated Universal Time (UTC), or is
	// not specified as either local time or UTC.
	struct DateTimeKind
	{
		enum type
		{
			Local = 2,
			Unspecified = 0,
			Utc = 1
		};
	};

	// Specifies the day of the week.
	struct DayOfWeek
	{
		enum type
		{
			Friday = 5,
			Monday = 1,
			Saturday = 6,
			Sunday = 0,
			Thursday = 4,
			Tuesday = 2,
			Wednesday = 3
		};
	};

	// Identifies the operating system, or platform, supported by an assembly.
	struct PlatformID
	{
		enum type
		{
			MacOSX = 6,
			Unix = 4,
			Win32S = 0,
			Win32Windows = 1,
			WinCE = 3,
			Xbox = 5
		};
	};

	// Specifies the culture, case, and sort rules to be used by certain overloads
	// of the String::Compare(String,String) and String::Equals(System.Object) methods.
	struct StringComparison
	{
		enum type
		{
			CurrentCulture,
			CurrentCultureIgnoreCase,
			InvariantCulture,
			InvariantCultureIgnoreCase,
			Ordinal,
			OrdinalIgnoreCase
		};
	};

	// Specifies whether applicable Overload:String::Split method overloads include or omit empty substrings from the return value.
	struct StringSplitOptions
	{
		enum type
		{
			None,
			RemoveEmptyEntries
		};
	};

	/**
	 * Specifies the type of an object.
	 */
	struct TypeCode
	{
		enum type
		{
			/**
			 * A null reference.
			 */
			Empty,
			/**
			 * A general type representing any reference or value type not explicitly represented by another TypeCode.
			 */
			Object,
			/**
			 * A database null (column) value.
			 */
			DBNull,
			/**
			 * A simple type representing Boolean values of true or false.
			 */
			Boolean,
			/**
			 * An integral type representing unsigned 8-bit integers with values between 0 and 255. The set of possible values for the System::TypeCode::Char type corresponds to the ASCII character set.
			 */
			Char,
			/**
			 * An integral type representing signed 8-bit integers with values between -128 and 127.
			 */
			SByte,
			/**
			 * An integral type representing unsigned 8-bit integers with values between 0 and 255.
			 */
			Byte,
			/**
			 * An integral type representing signed 16-bit integers with values between -32768 and 32767.
			 */
			Int16,
			/**
			 * An integral type representing unsigned 16-bit integers with values between 0 and 65535.
			 */
			UInt16,
			/**
			 * An integral type representing signed 32-bit integers with values between -2147483648 and 2147483647.
			 */
			Int32,
			/**
			 * An integral type representing unsigned 32-bit integers with values between 0 and 4294967295.
			 */
			UInt32,
			/**
			 * An integral type representing signed 64-bit integers with values between -9223372036854775808 and 9223372036854775807.
			 */
			Int64,
			/**
			 * An integral type representing unsigned 64-bit integers with values between 0 and 18446744073709551615.
			 */
			UInt64,
			/**
			 * A floating point type representing values ranging from approximately 1.5 x 10 -45 to 3.4 x 10 38 with a precision of 7 digits.
			 */
			Single,
			/**
			 * A floating point type representing values ranging from approximately 5.0 x 10 -324 to 1.7 x 10 308 with a precision of 15-16 digits.
			 */
			Double,
			/**
			 * A simple type representing values ranging from 1.0 x 10 -28 to approximately 7.9 x 10 28 with 28-29 significant digits.
			 */
			Decimal,
			/**
			 * A type representing a date and time value.
			 */
			DateTime = 16,
			/**
			 * A sealed class type representing ASCII character strings.
			 */
			String = 18,
		};
	};

	typedef DateTimeKind::type				DateTimeKind_t;
	typedef DayOfWeek::type					DayOfWeek_t;
	typedef PlatformID::type				PlatformID_t;
	typedef StringComparison::type			StringComparison_t;
	typedef StringSplitOptions::type		StringSplitOptions_t;
	typedef TypeCode::type					TypeCode_t;
}

#endif //_SYSTEM_ENUMS_
