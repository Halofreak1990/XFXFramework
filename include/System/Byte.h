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

		Byte(const Byte &obj);
		Byte(const byte &obj);

		int CompareTo(const Byte other) const;
		bool Equals(const Byte other) const;
		const char* ToString() const;
		static const char* ToString(byte value);

		bool operator!=(byte right) const;
		bool operator!=(const Byte right) const;
		bool operator==(byte right) const;
		bool operator==(const Byte right) const;
	};
}

#endif //_SYSTEM_BYTE_
