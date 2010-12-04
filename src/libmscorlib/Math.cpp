// Copyright (C) 2010-2012, Halofreak_1990
// All rights reserved.
// 
// Redistribution and use in source and binary forms, with or without 
// modification, are permitted provided that the following conditions are met:
// 
//     * Redistributions of source code must retain the above copyright 
//       notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above copyright 
//       notice, this list of conditions and the following disclaimer in the 
//       documentation and/or other materials provided with the distribution.
//     * Neither the name of the copyright holder nor the names of any 
//       contributors may be used to endorse or promote products derived from 
//       this software without specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE 
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE 
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR 
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF 
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS 
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN 
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE 
// POSSIBILITY OF SUCH DAMAGE.

#include <System/Math.h>

namespace System
{
	const double Math::E = 2.7182818284590451;
	const double Math::PI = 3.1415926535897931;
	
	double Math::Abs(double value)
	{
		return (value < 0) ? -value : value;
	}
	
	float Math::Abs(float value)
	{
		return (value < 0) ? -value : value;
	}
	
	int Math::Abs(int value)
	{
		return (value < 0) ? -value : value;
	}
	
	long long Math::Abs(long long value)
	{
		return (value < 0) ? -value : value;
	}

	sbyte Math::Abs(sbyte value)
	{
		return (value < 0) ? -value : value;
	}
	
	short Math::Abs(short value)
	{
		return (value < 0) ? -value : value;
	}
	
	double Math::Acos(double value)
	{
		return acos(value);
	}
	
	double Math::Asin(double value)
	{
		return asin(value);
	}
	
	double Math::Atan(double value)
	{
		return atan(value);
	}
	
	double Math::Atan2(double value1, double value2)
	{
		return atan2(value1, value2);
	}
	
	double Math::Ceiling(double value)
	{
		double result = Floor(value);
		if (result != value)
		{
			result++;
		}
		return result;
	}
	
	double Math::Cos(double value)
	{
		return cos(value);
	}
	
	double Math::Cosh(double value)
	{
		return cosh(value);
	}
	
	double Math::Exp(double value)
	{
		return exp(value);
	}
	
	double Math::Floor(double value)
	{
		return floor(value);
	}

	double Math::IEEERemainder(double value1, double value2)
	{
		double d = fmod(value1, value2);
		double num2 = d - (Abs(value2) * Sign(value1));
		if (Abs(num2) == Abs(d))
		{
			double a = value1 / value2;
			if (Abs(Round(a)) > Abs(a))
			{
				return num2;
			}
			return d;
		}
		if (Abs(num2) < Abs(d))
		{
			return num2;
		}
		return d;
	}
	
	double Math::Log(double value)
	{
		return log(value);
	}
	
	double Math::Log10(double value)
	{
		return log10(value);
	}
	
	byte Math::Max(byte value1, byte value2)
	{
		return (value1 > value2) ? value1 : value2;
	}

	double Math::Max(double value1, double value2)
	{
		return (value1 > value2) ? value1 : value2;
	}
	
	float Math::Max(float value1, float value2)
	{
		return (value1 > value2) ? value1 : value2;
	}
	
	int Math::Max(int value1, int value2)
	{
		return (value1 > value2) ? value1 : value2;
	}

	long long Math::Max(long long value1, long long value2)
	{
		return (value1 > value2) ? value1 : value2;
	}

	sbyte Math::Max(sbyte value1, sbyte value2)
	{
		return (value1 > value2) ? value1 : value2;
	}
	
	short Math::Max(short value1, short value2)
	{
		return (value1 > value2) ? value1 : value2;
	}

	uint Math::Max(uint value1, uint value2)
	{
		return (value1 > value2) ? value1 : value2;
	}

	ulong Math::Max(ulong value1, ulong value2)
	{
		return (value1 > value2) ? value1 : value2;
	}

	byte Math::Min(byte value1, byte value2)
	{
		return (value1 < value2) ? value1 : value2;
	}
	
	double Math::Min(double value1, double value2)
	{
		return (value1 < value2) ? value1 : value2;
	}
	
	float Math::Min(float value1, float value2)
	{
		return (value1 < value2) ? value1 : value2;
	}
	
	int Math::Min(int value1, int value2)
	{
		return (value1 < value2) ? value1 : value2;
	}

	long long Math::Min(long long value1, long long value2)
	{
		return (value1 < value2) ? value1 : value2;
	}

	sbyte Math::Min(sbyte value1, sbyte value2)
	{
		return (value1 < value2) ? value1 : value2;
	}
	
	short Math::Min(short value1, short value2)
	{
		return (value1 < value2) ? value1 : value2;
	}

	uint Math::Min(uint value1, uint value2)
	{
		return (value1 < value2) ? value1 : value2;
	}

	ulong Math::Min(ulong value1, ulong value2)
	{
		return (value1 < value2) ? value1 : value2;
	}

	ushort Math::Min(ushort value1, ushort value2)
	{
		return (value1 < value2) ? value1 : value2;
	}
	
	double Math::Pow(double value1, double value2)
	{
		return pow(value1, value2);
	}
	
	double Math::Round(double value)
	{
		return round(value);
	}
	
	double Math::Round(double value, int digits)
	{
		return ldexp(value, digits);
	}
	
	int Math::Sign(double value)
	{
		return (value < 0) ? -1 : (value > 0) ? 1 : 0;
	}
	
	int Math::Sign(float value)
	{
		return (value < 0) ? -1 : (value > 0) ? 1 : 0;
	}
	
	int Math::Sign(int value)
	{
		return (value < 0) ? -1 : (value > 0) ? 1 : 0;
	}
	
	int Math::Sign(long long value)
	{
		return (value < 0) ? -1 : (value > 0) ? 1 : 0;
	}

	int Math::Sign(sbyte value)
	{
		return (value < 0) ? -1 : (value > 0) ? 1 : 0;
	}
	
	int Math::Sign(short value)
	{
		return (value < 0) ? -1 : (value > 0) ? 1 : 0;
	}
	
	double Math::Sin(double value)
	{
		return sin(value);
	}
	
	double Math::Sinh(double value)
	{
		return sinh(value);
	}
	
	double Math::Sqrt(double value)
	{
		return sqrt(value);
	}
	
	double Math::Tan(double value)
	{
		return tan(value);
	}
	
	double Math::Tanh(double value)
	{
		return tanh(value);
	}
}
