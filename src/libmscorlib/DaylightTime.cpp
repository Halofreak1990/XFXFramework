#include <System/Globalization/DaylightTime.h>

namespace System
{
	namespace Globalization
	{
		DaylightTime::DaylightTime(const DateTime start, const DateTime end, const TimeSpan delta)
			: Delta(delta), End(end), Start(start)
		{
		}

		DaylightTime::DaylightTime(const DaylightTime &obj)
			: Delta(obj.Delta), End(obj.End), Start(obj.Start)
		{
		}

		bool DaylightTime::Equals(const DaylightTime other) const
		{
			return ((Delta == other.Delta) && (End == other.End) && (Start == other.Start));
		}

		bool DaylightTime::operator !=(const DaylightTime& right) const
		{
			return !Equals(right);
		}

		bool DaylightTime::operator ==(const DaylightTime& right) const
		{
			return Equals(right);
		}
	}
}
