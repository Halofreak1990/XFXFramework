/********************************************************
 *	MathHelper.h										*
 *														*
 *	XFX MathHelper definition file						*
 *	Copyright © XFX Team. All Rights Reserved			*
 ********************************************************/
#ifndef _SYSTEM_MATHHELPER_
#define _SYSTEM_MATHHELPER_

namespace XFX
{
	/// <summary>
	/// Contains commonly used precalculated values.
	/// </summary>
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

		static float Baricentric(float value1, float value2, float value3, float amount1, float amount2);
		static float CatmullRom(float value1, float value2, float value3, float value4, float amount);
		static float Clamp(float value, float min, float max);
		static float Distance(float value1, float value2);
		static float Hermite(float value1, float tangent1, float value2, float tangent2, float amount);
		static float Lerp(float value1, float value2, float amount);
		static float Max(float value1, float value2);
		static float Min(float value1, float value2);
		static float SmoothStep(float value1, float value2, float amount);
		static float ToDegrees(float radians);
		static float ToRadians(float degrees);
	};
}

#endif //_SYSTEM_MATHHELPER_
