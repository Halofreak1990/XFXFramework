/*****************************************************************************
 *	Single.h																 *
 *																			 *
 *	XFX System::Single structure definition file							 *
 *	Copyright (c) XFX Team. All Rights Reserved 							 *
 *****************************************************************************/
#ifndef _SYSTEM_SINGLE_
#define _SYSTEM_SINGLE_

#include <System/Interfaces.h>
#include <System/Object.h>

namespace System
{
	class String;

	// Represents a single precision floating point value.
	struct Single : IComparable<Single>, IEquatable<Single>, Object
	{
	private:
		float value;

	public:
		static const float Epsilon;
		static const float MaxValue;
		static const float MinValue;
		static const float NaN;
		static const float NegativeInfinity;
		static const float PositiveInfinity;

		Single();
		Single(const Single &obj);
		Single(const float &obj);

		int CompareTo(const Single other) const;
		bool Equals(Object const * const obj) const;
		bool Equals(const Single other) const;
		int GetHashCode() const;
		static int GetType();
		const String& ToString() const;
		static const String& ToString(const float value);
		static bool TryParse(const String& str, out float* result);

		operator float() const;
		bool operator !=(const Single& right) const;
		bool operator ==(const Single& right) const;
	};
}

#endif //_SYSTEM_SINGLE_
