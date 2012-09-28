#ifndef _SYSTEM_GLOBALIZATION_ENUMS_
#define _SYSTEM_GLOBALIZATION_ENUMS_

namespace System
{
	namespace Globalization
	{
		// Defines different rules for determining the first week of the year.
		struct CalendarWeekRule
		{
			enum type
			{
				FirstDay = 0,
				FirstFourDayWeek = 2,
				FirstFullWeek = 1
			};
		};

		// Defines the string comparison options to use with System.Globalization.CompareInfo.
		struct CompareOptions
		{
			enum type
			{
				IgnoreCase = 1,
				IgnoreKanaType = 8,
				IgnoreNonSpace = 2,
				IgnoreSymbols = 4,
				IgnoreWidth = 16,
				None = 0,
				Ordinal = 1073741824,
				OrdinalIgnoreCase = 268435456,
				StringSort = 536870912
			};
		};

		// Defines the formatting options that customize string parsing for the System::DateTime::Parse and
		// System::DateTime::ParseExact methods.
		struct DateTimeStyles
		{
			enum type
			{
				AdjustToUniversal = 16,
				AllowInnerWhite = 4,
				AllowLeadingWhite = 1,
				AllowTrailingWhite = 2,
				AllowWhiteSpaces = 7,
				AssumeLocal = 32,
				AssumeUniversal = 64,
				NoCurrentDateDefault = 8,
				None = 0,
				RoundtripKind = 128
			};
		};

		// Defines the different language versions of the Gregorian calendar.
		struct GregorianCalenderTypes
		{
			enum type
			{
				Arabic = 10,
				Localized = 1,
				MiddleEastFrench = 9,
				TransliteratedEnglish = 11,
				TransliteratedFrench = 12,
				USEnglish = 2
			};
		};

		// Determines the styles permitted in numeric string arguments that are passed to the Parse methods of the
		// numeric base type classes.
		struct NumberStyles
		{
			enum type
			{
				AllowCurrencySymbol = 256,
				AllowDecimalPoint = 32,
				AllowExponent = 128,
				AllowHexSpecifier = 512,
				AllowLeadingSign = 4,
				AllowLeadingWhite = 1,
				AllowParentheses = 16,
				AllowThousands = 64,
				AllowTrailingSign = 8,
				AllowTrailingWhite = 2,
				Any = 511,
				Currency = 383,
				Float = 167,
				HexNumber = 515,
				Integer = 7,
				None = 0,
				Number = 111
			};
		};

		typedef CalendarWeekRule::type			CalendarWeekRule_t;
		typedef CompareOptions::type			CompareOptions_t;
		typedef DateTimeStyles::type			DateTimeStyles_t;
		typedef GregorianCalenderTypes::type	GregorianCalenderTypes_t;
		typedef NumberStyles::type				NumberStyles_t;
	}
}

#endif //_SYSTEM_GLOBALIZATION_ENUMS_
