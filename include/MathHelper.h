/********************************************************
 *	MathHelper.h										*
 *														*
 *	XFX MathHelper definition file						*
 *	Copyright © XFX Team. All Rights Reserved			*
 ********************************************************/
#ifndef _XFX_MATHHELPER_
#define _XFX_MATHHELPER_

namespace XFX
{
	// Contains commonly used precalculated values.
	class MathHelper
	{
	private:
		MathHelper(); // Private constructor to prevent instantiation.

	public:
		static const float E;
		static const float Log10E;
		static const float Log2E;
		static const float Pi;
		static const float PiOver2;
		static const float PiOver4;
		static const float TwoPi;

		static float Baricentric(const float value1, const float value2, const float value3, const float amount1, const float amount2);
		static float CatmullRom(const float value1, const float value2, const float value3, const float value4, const float amount);
		static float Clamp(const float value, const float min, const float max);
		static float Distance(const float value1, const float value2);
		static float Hermite(const float value1, const float tangent1, const float value2, const float tangent2, const float amount);
		static float Lerp(const float value1, const float value2, const float amount);
		static float Max(const float value1, const float value2);
		static float Min(const float value1, const float value2);
		static float SmoothStep(const float value1, const float value2, const float amount);
		static float ToDegrees(const float radians);
		static float ToRadians(const float degrees);
	};
}

#endif //_XFX_MATHHELPER_
