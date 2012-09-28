/********************************************************
 *	Math.h												*
 *														*
 *	XFX Math definition file							*
 *	Copyright © XFX Team. All Rights Reserved			*
 ********************************************************/
#ifndef _SYSTEM_MATH_
#define _SYSTEM_MATH_

#include "Types.h"

namespace System
{
	// Provides constants and static methods for trigonometric, logarithmic, and other common mathematical functions.
	class Math
	{
	private:
		Math(); //! Private constructor to prevent instantiation

	public:
		static const double E;
		static const double PI;
		
		static double Abs(double value);
		static float Abs(float value);
		static int Abs(int value);
		static long long Abs(long long value);
		static sbyte Abs(sbyte value);
		static short Abs(short value);
		static double Acos(double value);
		static double Asin(double value);
		static double Atan(double value);
		static double Atan2(double value1, double value2);
		static double Ceiling(double value);
		static double Cos(double value);
		static double Cosh(double value);
		static double Exp(double value);
		static double Floor(double value);
		static double IEEERemainder(double value1, double value2);
		static double Log(double value);
		static double Log10(double value);
		static byte Max(byte value1, byte value2);
		static double Max(double value1, double value2);
		static float Max(float value1, float value2);
		static int Max(int value1, int value2);
		static long long Max(long long value1, long long value2);
		static sbyte Max(sbyte value1, sbyte value2);
		static short Max(short value1, short value2);
		static uint Max(uint value1, uint value2);
		static ulong Max(ulong value1, ulong value2);
		static byte Min(byte value1, byte value2);
		static double Min(double value1, double value2);
		static float Min(float value1, float value2);
		static int Min(int value1, int value2);
		static long long Min(long long value1, long long value2);
		static sbyte Min(sbyte value1, sbyte value2);
		static short Min(short value1, short value2);
		static uint Min(uint value1, uint value2);
		static ulong Min(ulong value1, ulong value2);
		static ushort Min(ushort value1, ushort value2);
		static double Pow(double x, double y);
		static double Round(double value);
		static double Round(double value, int digits);
		static int Sign(double value);
		static int Sign(float value);
		static int Sign(int value);
		static int Sign(long long value);
		static int Sign(sbyte value);
		static int Sign(short value);
		static double Sin(double value);
		static double Sinh(double value);
		static double Sqrt(double value);
		static double Tan(double value);
		static double Tanh(double value);
	};
}

#endif //_SYSTEM_MATH_
