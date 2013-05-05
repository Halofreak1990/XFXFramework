#ifndef _SYSTEM_UINT64_
#define _SYSTEM_UINT64_

#include <System/Interfaces.h>

namespace System
{
	class String;

	// Represents an unsigned, 64-bit integer.
	struct UInt64 : IComparable<UInt64>, IEquatable<UInt64>, Object
	{
	private:
		ulong value;

	public:
		static const ulong MaxValue;
		static const ulong MinValue;

		UInt64(const UInt64 &obj);
		UInt64(const ulong &obj);

		int CompareTo(const UInt64 other) const;
		bool Equals(Object const * const obj) const;
		bool Equals(const UInt64 other) const;
		int GetHashCode() const;
		int GetType() const;
		const char* ToString() const;
		static const char* ToString(const ulong value);
		static bool TryParse(const String& str, out ulong* value);

		operator ulong() const;
		bool operator==(const UInt64& right) const;
		//bool operator==(const ulong& right) const;
		bool operator!=(const UInt64& right) const;
		//bool operator!=(const ulong& right) const;
	};
}

#endif //_SYSTEM_UINT64_
