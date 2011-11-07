// Copyright (C) 2010-2012, XFX Team
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

#include <MathHelper.h>

namespace XFX
{
	const float MathHelper::E = 2.718282f;
	const float MathHelper::Log10E = 0.4342945f;
	const float MathHelper::Log2E = 1.442695f;
	const float MathHelper::Pi = 3.141593f;
	const float MathHelper::PiOver2 = 1.570796f;
	const float MathHelper::PiOver4 = 0.7853982f;
	const float MathHelper::TwoPi = 6.283185f;

	float MathHelper::Baricentric(float value1, float value2, float value3, float amount1, float amount2)
	{
		return (value1 + (amount1 * (value2 - value1))) + (amount2 * (value3 - value1));
	}

	float MathHelper::CatmullRom(float value1, float value2, float value3, float value4, float amount)
	{
	    float squared = amount * amount; 
        float cubed = amount * squared; 

		return 0.5f * ((((2.0f * value2) + ((-value1 + value3) * amount)) +  
                         (((((2.0f * value1) - (5.0f * value2)) + (4.0f * value3)) - value4) * squared)) +  
                         ((((-value1 + (3.0f * value2)) - (3.0f * value3)) + value4) * cubed)); 
	}

	float MathHelper::Clamp(float value, float min, float max)
	{
		float x = value;
		x = (x > max) ? max : x; 
                x = (x < min) ? min : x;
		return x;
	}

	float MathHelper::Distance(float value1, float value2)
	{
		return value1 - value2;
	}

	float MathHelper::Hermite(float value1, float tangent1, float value2, float tangent2, float amount)
	{
		float squared = amount * amount; 
                float cubed = amount * squared;
		float part1 = ((2.0f * cubed) - (3.0f * squared)) + 1.0f; 
                float part2 = (-2.0f * cubed) + (3.0f * squared); 
                float part3 = (cubed - (2.0f * squared)) + amount; 
                float part4 = cubed - squared; 

		return (((value1 * part1) + (value2 * part2)) + (tangent1 * part3)) + (tangent2 * part4);
	}

	float MathHelper::Lerp(float value1, float value2, float amount)
	{
		return value1 + ((value2 - value1) * amount); 
	}
	
	float MathHelper::Max(float value1, float value2)
	{
		return (value1 > value2) ? value2 : value1;
	}

	float MathHelper::Min(float value1, float value2)
	{
		return (value1 < value2) ? value1 : value2;
	}

	float MathHelper::SmoothStep(float value1, float value2, float amount)
	{
		amount = (amount > 1.0f) ? 1.0f : ((amount < 0.0f) ? 0.0f : amount); 
                amount = (amount * amount) * (3.0f - (2.0f * amount)); 
		return value1 + ((value2 - value1) * amount);
	}
	
	float MathHelper::ToDegrees(float radians)
	{
		return radians * 180 / Pi;
	}

	float MathHelper::ToRadians(float degrees)
	{
		return degrees * Pi / 180;
	}
}
