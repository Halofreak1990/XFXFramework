#ifndef _DAYLIGHTTIME_
#define _DAYLIGHTTIME_

#include <System/DateTime.h>
#include <System/TimeSpan.h>

namespace System
{
	namespace Globalization
	{
		/// <summary>
		/// Defines the period of daylight saving time.
		/// </summary>
		class DaylightTime
		{
		private:
			DateTime _start;
			DateTime _end;
			TimeSpan _delta;

		public:
			TimeSpan Delta();
			DateTime End();
			DateTime Start();

			DaylightTime(DateTime start, DateTime end, DateTime delta);
		};
	}
}

#endif //_DAYLIGHTTIME_
