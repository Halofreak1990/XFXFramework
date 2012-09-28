#ifndef _SYSTEM_INT32_
#define _SYSTEM_INT32_

#include "Interfaces.h"

namespace System
{
	// Represents a signed, 32-bit integer.
	struct Int32 : IComparable<Int32>, IEquatable<Int32>, Object
	{
	private:
		int value;

	public:
		static const int MaxValue;
		static const int MinValue;
		int getValue() const;

		Int32(const Int32 &obj);
		Int32(const int &obj);

		int CompareTo(const Int32 other) const;
		bool Equals(const Object* obj) const;
		bool Equals(const Int32 other) const;
		int GetHashCode() const;
		int GetType() const;
		const char* ToString() const;
		static const char* ToString(const int value);
		static bool TryParse(const String& str, out int result);

		bool operator !=(const Int32 right) const;
		bool operator ==(const Int32 right) const;
	};
}

#endif //_SYSTEM_INT32_
