/********************************************************
 *	Single.h											*
 *														*
 *	XFX Single structure definition file				*
 *	Copyright © XFX Team. All Rights Reserved			*
 ********************************************************/
#ifndef _SYSTEM_SINGLE_
#define _SYSTEM_SINGLE_

#include <System/Interfaces.h>
#include <System/Object.h>

namespace System
{
	// Represents a single precision floating point value.
	struct Single : public IComparable<Single>, public IEquatable<Single>, virtual Object
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

		Single(const Single &obj);
		Single(const float &obj);

		int CompareTo(const Single other) const;
		bool Equals(const Single other) const;
		int GetHashCode() const;
		int GetType() const;
		static float Parse(char* str);
		const char* ToString() const;

		bool operator !=(const float right) const;
		bool operator !=(const Single right) const;
		bool operator ==(const float right) const;
		bool operator ==(const Single right) const;
	};
}

#endif //_SYSTEM_SINGLE_
