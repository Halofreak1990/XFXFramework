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

		Single(float f);

		int CompareTo(Single other);
		bool Equals(Single other);
		static float Parse(char* str);
		char* ToString();

		bool operator !=(float right);
		bool operator !=(Single right);
		bool operator ==(float right);
		bool operator ==(Single right);
	};
}

#endif //_SYSTEM_SINGLE_
