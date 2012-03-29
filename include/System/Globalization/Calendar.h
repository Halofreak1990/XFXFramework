
#ifndef _SYSTEM_GLOBALIZATION_CALENDAR_
#define _SYSTEM_GLOBALIZATION_CALENDAR_

#include <System/Object.h>

namespace System
{
	class DateTime;

	namespace Globalization
	{
		// Represents time in divisions, such as weeks, months, and years.
		class Calendar : virtual Object
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
