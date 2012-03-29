#ifndef _DAYLIGHTTIME_
#define _DAYLIGHTTIME_

#include <System/DateTime.h>
#include <System/TimeSpan.h>

namespace System
{
	namespace Globalization
	{
		// Defines the period of daylight saving time.
		class DaylightTime : public IEquatable<DaylightTime>, virtual Object
		{
		public:
			const TimeSpan Delta;
			const DateTime End;
			const DateTime Start;

			DaylightTime(const DateTime start, const DateTime end, const TimeSpan delta);
			DaylightTime(const DaylightTime &obj);

			bool Equals(const DaylightTime other) const;

			bool operator !=(const DaylightTime right) const;
			bool operator ==(const DaylightTime right) const;
		};
	}
}

#endif //_DAYLIGHTTIME_
