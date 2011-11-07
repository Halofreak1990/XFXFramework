#ifndef _SYSTEM_DOUBLE_
#define _SYSTEM_DOUBLE_

#include <System/Interfaces.h>
#include <System/Object.h>

namespace System
{
	// Represents a double precision floating point value.
	struct Double : public IComparable<Double>, public IEquatable<Double>, virtual Object
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

		Double(double d);

		int CompareTo(Double other);
		bool Equals(Double other);
		static double Parse(char* str);
		char* ToString();

		bool operator !=(double right);
		bool operator !=(Double right);
		bool operator ==(double right);
		bool operator ==(Double right);
	};
}

#endif //_SYSTEM_DOUBLE_
