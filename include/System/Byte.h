/*****************************************************************************
 *	Byte.h																	 *
 *																			 *
 *	XFX System::Byte structure definition file  							 *
 *	Copyright (c) XFX Team. All Rights Reserved 							 *
 *****************************************************************************/
#ifndef _SYSTEM_BYTE_
#define _SYSTEM_BYTE_

#include "Interfaces.h"
#include "Object.h"

namespace System
{
	class String;

	// Represents an 8-bit unsigned integer.
	struct Byte : IComparable<Byte>, IEquatable<Byte>, Object
	{
	private:
		byte value;

	public:
		static const byte MaxValue;
		static const byte MinValue;

		Byte();
		Byte(const Byte &obj);
		Byte(const byte &obj);

		int CompareTo(const Byte other) const;
		bool Equals(const Byte other) const;
		static int GetType();
		const String& ToString() const;
		static const String& ToString(const byte value);
		static bool TryParse(const String& str, out byte* result);

		operator byte() const;
		bool operator!=(const Byte& right) const;
		bool operator==(const Byte& right) const;
	};
}

#endif //_SYSTEM_BYTE_
