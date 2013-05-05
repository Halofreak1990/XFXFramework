#ifndef _SYSTEM_BOOLEAN_
#define _SYSTEM_BOOLEAN_

#include "Interfaces.h"

namespace System
{
	class String;

	// Represents a Boolean value.
	struct Boolean : IComparable<Boolean>, IEquatable<Boolean>, Object
	{
	private:
		bool value;

	public:
		Boolean();
		Boolean(const Boolean &obj);
		Boolean(const bool &obj);

		static const char* TrueString;
		static const char* FalseString;

		int CompareTo(const Boolean other) const;
		bool Equals(Object const * const obj) const;
		bool Equals(const Boolean other) const;
		int GetType() const;
		static bool Parse(const String& str);
		const char* ToString() const;
		static const char* ToString(bool value);

		operator bool() const;
		bool operator!=(const Boolean& right) const;
		bool operator==(const Boolean& right) const;
	};
}

#endif //_BOOLEAN_
