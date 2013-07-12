/*****************************************************************************
 *	Int64.h 																 *
 *																			 *
 *	XFX System::Int64 structure definition file 							 *
 *	Copyright (c) XFX Team. All Rights Reserved 							 *
 *****************************************************************************/
#ifndef _SYSTEM_INT64_
#define _SYSTEM_INT64_

#include <System/Interfaces.h>

namespace System
{
	class String;

	/**
	 * Represents a signed, 64-bit integer.
	 */
	struct Int64 : IComparable<Int64>, IEquatable<Int64>, Object
	{
	private:
		long long value;

	public:
		static const long long MaxValue;
		static const long long MinValue;

		Int64();
		Int64(const Int64 &obj);
		Int64(const long long &obj);

		int CompareTo(const Int64 other) const;
		bool Equals(Object const * const obj) const;
		bool Equals(const Int64 other) const;
		int GetHashCode() const;
		static const Type& GetType();
		const String ToString() const;
		static const String ToString(const long long value);
		static bool TryParse(const String& str, out long long* result);

		operator long long() const;
		bool operator==(const Int64& right) const;
		bool operator!=(const Int64& right) const;
	};
}

#endif //_SYSTEM_INT64_
