/*****************************************************************************
 *	CurveKey.h  															 *
 *																			 *
 *	XFX::CurveKey class declaration file									 *
 *	Copyright (c) XFX Team. All Rights Reserved 							 *
 *****************************************************************************/
#ifndef _XFX_CURVEKEY_
#define _XFX_CURVEKEY_

#include <System/Interfaces.h>
#include "Enums.h"

using namespace System;

namespace XFX
{
	/**
	 * Represents a point in a multi-point curve.
	 */
	class CurveKey : public IComparable<CurveKey>, public IEquatable<CurveKey>, public Object
	{
	private:
		float position;

	public:
		CurveContinuity_t Continuity;
		float getPosition() const;
		float TangentIn;
		float TangentOut;
		float Value;

		CurveKey(float position, float value);
		CurveKey(float position, float value, float tangentIn, float tangentOut);
		CurveKey(float position, float value, float tangentIn, float tangentOut, CurveContinuity_t continuity);

		CurveKey Clone();
		int CompareTo(const CurveKey other) const;
		bool Equals(Object const * const obj) const;
		bool Equals(const CurveKey other) const;
		int GetHashCode() const;
		static const Type& GetType();

		bool operator!=(const CurveKey& right) const;
		bool operator==(const CurveKey& right) const;
	};
}

#endif //_XFX_CURVEKEY_
