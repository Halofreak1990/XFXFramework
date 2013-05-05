#ifndef _SYSTEM_GLOBALIZATION_DAYLIGHTTIME_
#define _SYSTEM_GLOBALIZATION_DAYLIGHTTIME_

#include <System/DateTime.h>
#include <System/TimeSpan.h>

namespace System
{
	namespace Globalization
	{
		// Defines the period of daylight saving time.
		class DaylightTime : public IEquatable<DaylightTime>, public Object
		{
		public:
			const TimeSpan Delta;
			const DateTime End;
			const DateTime Start;

			DaylightTime(const DateTime start, const DateTime end, const TimeSpan delta);
			DaylightTime(const DaylightTime &obj);

			bool Equals(const DaylightTime other) const;
			int GetType() const;

			bool operator !=(const DaylightTime& right) const;
			bool operator ==(const DaylightTime& right) const;
		};
	}
}

#endif //_SYSTEM_GLOBALIZATION_DAYLIGHTTIME_
