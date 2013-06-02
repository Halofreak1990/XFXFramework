/*****************************************************************************
 *	UInt16.h																 *
 *																			 *
 *	XFX System::UInt16 definition file  									 *
 *	Copyright (c) XFX Team. All Rights Reserved 							 *
 *****************************************************************************/
#ifndef _SYSTEM_UINT16_
#define _SYSTEM_UINT16_

#include <System/Interfaces.h>

namespace System
{
	class String;

	// Represents an unsigned, 16-bit integer.
	struct UInt16 : IComparable<UInt16>, IEquatable<UInt16>, Object
	{
	private:
		ushort value;

	public:
		static const ushort MaxValue;
		static const ushort MinValue;

		UInt16();
		UInt16(const UInt16 &obj);
		UInt16(const ushort &obj);

		int CompareTo(const UInt16 other) const;
		bool Equals(Object const * const obj) const;
		bool Equals(const UInt16 other) const;
		int GetHashCode() const;
		int GetType() const;
		const String& ToString() const;
		static const String& ToString(const ushort value);
		static bool TryParse(const String& str, out ushort* result);

		operator ushort() const;
		bool operator==(const UInt16& right) const;
		bool operator!=(const UInt16& right) const;
	};
}

#endif //_SYSTEM_UINT16_
