/*****************************************************************************
 *	Curve.h 																 *
 *																			 *
 *	XFX::Curve class declaration file										 *
 *	Copyright (c) XFX Team. All Rights Reserved 							 *
 *****************************************************************************/
#ifndef _XFX_CURVE_
#define _XFX_CURVE_

#include <System/Type.h>
#include "CurveKeyCollection.h"

using namespace System;

namespace XFX
{
	/**
	 * Stores an arbitrary collection of 2D CurveKey points, and provides methods for evaluating features of the curve they define.
	 */
	class Curve
	{
	private:
		CurveKeyCollection keys;

		float GetCurvePosition(float position);
		int GetNumberOfCycle(float position);

	public:
		bool IsConstant() const;
		CurveKeyCollection getKeys() const;
		CurveLoopType_t PostLoop;
		CurveLoopType_t PreLoop;

		Curve();

		Curve       Clone() const;
		void        ComputeTangent(int keyIndex, CurveTangent_t tangentInType, CurveTangent_t tangentOutType);
		inline void ComputeTangent(int keyIndex, CurveTangent_t tangentType) { ComputeTangent(keyIndex, tangentType, tangentType); }
		void        ComputeTangents(CurveTangent_t tangentInType, CurveTangent_t tangentOutType);
		inline void ComputeTangents(CurveTangent_t tangentType) { ComputeTangents(tangentType, tangentType); }
		float       Evaluate(float position);
		static const Type& GetType();
	};
}

#endif //_XFX_CURVE_
