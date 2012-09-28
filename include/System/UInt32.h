#ifndef _SYSTEM_UINT32_
#define _SYSTEM_UINT32_

#include <System/Interfaces.h>

namespace System
{
	// Represents an unsigned, 32-bit integer.
	struct UInt32 : IComparable<UInt32>, IEquatable<UInt32>, Object
	{
	private:
		uint value;

	public:
		static const uint MaxValue;
		static const uint MinValue;

		UInt32(const UInt32 &obj);
		UInt32(const uint &obj);

		int CompareTo(const UInt32 other) const;
		bool Equals(const Object* obj) const;
		bool Equals(const UInt32 other) const;
		int GetHashCode() const;
		int GetType() const;
		const char* ToString() const;
		static const char* ToString(const uint value);
		static bool TryParse(const String& str, out uint result);

		bool operator==(const UInt32& right) const;
		bool operator!=(const UInt32& right) const;
	};
}

#endif //_SYSTEM_UINT32_
