#ifndef _SYSTEM_BOOLEAN_
#define _SYSTEM_BOOLEAN_

#include "Interfaces.h"

namespace System
{
	// Represents a Boolean value.
	struct Boolean : public IComparable<Boolean>, public IEquatable<Boolean>, virtual Object
	{
	private:
		bool value;

	public:
		Boolean(const Boolean &obj);
		Boolean(const bool &obj); // Copy constructor

		static const char* True;
		static const char* False;

		int CompareTo(const Boolean other) const;
		bool Equals(const Boolean other) const;
		bool Parse(char* str);
		const char* ToString() const;
		static const char* ToString(bool value);

		bool operator!=(bool right) const;
		bool operator!=(const Boolean right) const;
		bool operator==(bool right) const;
		bool operator==(const Boolean right) const;
	};
}

#endif //_BOOLEAN_
