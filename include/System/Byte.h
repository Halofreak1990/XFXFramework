#ifndef _BYTE_
#define _BYTE_

#include "Types.h"

namespace System
{
	struct Byte
	{
	private:
		byte value;

	public:
		static const byte MaxValue;
		static const byte MinValue;

		Byte(const byte &obj);

		int CompareTo(byte other);
		int CompareTo(Byte other);
		char* ToString();
		static char* ToString(byte value);

		bool operator!=(byte right);
		bool operator!=(Byte right);
		bool operator==(byte right);
		bool operator==(Byte right);
		Byte operator =(byte right);
		Byte operator =(Byte right);
	};
}

#endif //_BYTE_
