/*****************************************************************************
 *	Int32.h																	 *
 *																			 *
 *	XFX System::Int32 definition file  										 *
 *	Copyright (c) XFX Team. All Rights Reserved 							 *
 *****************************************************************************/
#ifndef _SYSTEM_INT32_
#define _SYSTEM_INT32_

#include "Interfaces.h"

namespace System
{
	class String;

	// Represents a signed, 32-bit integer.
	struct Int32 : IComparable<Int32>, IEquatable<Int32>, Object
	{
	private:
		int value;

	public:
		static const int MaxValue;
		static const int MinValue;

		Int32();
		Int32(const Int32 &obj);
		Int32(const int &obj);

		int CompareTo(const Int32 other) const;
		bool Equals(Object const * const obj) const;
		bool Equals(const Int32 other) const;
		int GetHashCode() const;
		static int GetType();
		const String ToString() const;
		static const String ToString(const int value);
		static bool TryParse(const String& str, out int* result);

		operator int() const;
		bool operator !=(const Int32& right) const;
		bool operator ==(const Int32& right) const;
	};
}

#endif //_SYSTEM_INT32_
