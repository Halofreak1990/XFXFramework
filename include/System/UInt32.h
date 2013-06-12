/*****************************************************************************
 *	UInt32.h																 *
 *																			 *
 *	XFX System::UInt32 definition file  									 *
 *	Copyright (c) XFX Team. All Rights Reserved 							 *
 *****************************************************************************/
#ifndef _SYSTEM_UINT32_
#define _SYSTEM_UINT32_

#include <System/Interfaces.h>

namespace System
{
	// Represents an unsigned, 32-bit integer.
	struct UInt32 : IComparable<UInt32>, IEquatable<UInt32>, Object
	{
	private:
		uint value;

	public:
		static const uint MaxValue;
		static const uint MinValue;

		UInt32(const UInt32 &obj);
		UInt32(const uint &obj);

		int CompareTo(const UInt32 other) const;
		bool Equals(Object const * const obj) const;
		bool Equals(const UInt32 other) const;
		int GetHashCode() const;
		int GetType() const;
		const String& ToString() const;
		static const String& ToString(const uint value);
		static bool TryParse(const char* str, out uint* result);

		operator uint() const;
		bool operator==(const UInt32& right) const;
		bool operator!=(const UInt32& right) const;
	};
}

#endif //_SYSTEM_UINT32_
