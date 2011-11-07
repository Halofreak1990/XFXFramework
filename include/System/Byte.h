/********************************************************
 *	Byte.h												*
 *														*
 *	XFX Byte structure definition file					*
 *	Copyright © XFX Team. All Rights Reserved			*
 ********************************************************/
#ifndef _SYSTEM_BYTE_
#define _SYSTEM_BYTE_

#include "Interfaces.h"
#include "Object.h"

namespace System
{
	// Represents an 8-bit unsigned integer.
	struct Byte : public IComparable<Byte>, public IEquatable<Byte>, virtual Object
	{
	private:
		byte value;

	public:
		static const byte MaxValue;
		static const byte MinValue;

		Byte(byte b);

		int CompareTo(Byte other);
		bool Equals(Byte other);
		char* ToString();
		static char* ToString(byte value);

		bool operator!=(byte right);
		bool operator!=(Byte right);
		bool operator==(byte right);
		bool operator==(Byte right);
	};
}

#endif //_SYSTEM_BYTE_
