/*****************************************************************************
 *	SByte.h 																 *
 *																			 *
 *	XFX System::SByte definition file										 *
 *	Copyright (c) XFX Team. All Rights Reserved 							 *
 *****************************************************************************/
#ifndef _SYSTEM_SBYTE_
#define _SYSTEM_SBYTE_

#include <System/Interfaces.h>

namespace System
{
	class String;

	// Represents a signed 8-bit integer.
	struct SByte : IComparable<SByte>, IEquatable<SByte>, Object
	{
	private:
		sbyte value;

	public:
		static const sbyte MaxValue;
		static const sbyte MinValue;

		SByte();
		SByte(const SByte &obj);
		SByte(const sbyte &obj);

		int CompareTo(const SByte other) const;
		bool Equals(Object const * const obj) const;
		bool Equals(const SByte other) const;
		int GetHashCode() const;
		int GetType() const;
		const String& ToString() const;
		static const String& ToString(const sbyte value);
		static bool TryParse(const String& str, out sbyte* value);

		operator sbyte() const;
		bool operator==(const SByte& right) const;
		//bool operator==(const sbyte& right) const;
		bool operator!=(const SByte& right) const;
		//bool operator!=(const sbyte& right) const;
	};
}

#endif //_SYSTEM_SBYTE_
