#ifndef _SYSTEM_GLOBALIZATION_CALENDAR_
#define _SYSTEM_GLOBALIZATION_CALENDAR_



namespace System
{
	class DateTime;

	namespace Globalization
	{
		/// <summary>
		/// Represents time in divisions, such as weeks, months, and years.
		/// </summary>
		class Calendar
		{
		public:
			DateTime AddDays(DateTime time, int days);
			DateTime AddHours(DateTime time, int hours);
			DateTime AddMilliseconds(DateTime time, double milliseconds);
			DateTime AddMinutes(DateTime time, int minutes);
			DateTime AddMonths(DateTime time, int months);
		};
	}
}

#endif //_SYSTEM_GLOBALIZATION_CALENDAR_
