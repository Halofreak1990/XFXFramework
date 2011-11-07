#ifndef _SYSTEM_BOOLEAN_
#define _SYSTEM_BOOLEAN_

#include "Interfaces.h"

namespace System
{
	struct Boolean : public IComparable<Boolean>, public IEquatable<Boolean>, virtual Object
	{
	private:
		bool value;

	public:
		Boolean(const bool &obj); // Copy constructor

		static const char* True;
		static const char* False;

		int CompareTo(Boolean other);
		bool Equals(Boolean other);
		bool Parse(char* str);
		char* ToString();
		static char* ToString(bool value);

		bool operator!=(bool right);
		bool operator!=(Boolean right);
		bool operator==(bool right);
		bool operator==(Boolean right);
	};
}

#endif //_BOOLEAN_
