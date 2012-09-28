#ifndef _SYSTEM_DOUBLE_
#define _SYSTEM_DOUBLE_

#include <System/Interfaces.h>
#include <System/Object.h>

namespace System
{
	// Represents a double precision floating point value.
	struct Double : IComparable<Double>, IEquatable<Double>, Object
	{
	private:
		double value;

	public:
		static const double Epsilon;
		static const double MaxValue;
		static const double MinValue;
		static const double NaN;
		static const double NegativeInfinity;
		static const double PositiveInfinity;

		Double(const double &obj);
		Double(const Double &obj);

		int CompareTo(const Double other) const;
		bool Equals(const Double other) const;
		int GetHashCode() const;
		int GetType() const;
		static double Parse(char* str);
		const char* ToString() const;
		static const char* ToString(const double value);

		bool operator !=(const Double right) const;
		bool operator ==(const Double right) const;
	};
}

#endif //_SYSTEM_DOUBLE_
