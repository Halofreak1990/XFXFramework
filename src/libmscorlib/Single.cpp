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

#include <System/Single.h>
#include <System/String.h>
#include <stdlib.h>
#include <string.h>

unsigned int rawNaNF = 0x7ff80000UL;
unsigned int rawPosInfF = 0x7ff00000UL;
unsigned int rawNegInfF = 0xfff00000UL;

namespace System
{
	const float Single::Epsilon = 1.4013e-045f;
	const float Single::MaxValue = 3.40282e+038f;
	const float Single::MinValue = -3.40282e+038f;
	const float Single::NaN = *( float* )&rawNaNF;
	const float Single::PositiveInfinity = *( float* )&rawPosInfF;
	const float Single::NegativeInfinity = *( float* )&rawNegInfF;

	Single::Single(const Single &obj)
	{
		value = obj.value;
	}

	Single::Single(const float &obj)
	{
		value = obj;
	}

	int Single::CompareTo(const Single other) const
	{
		if (value > other.value)
			return 1;
		if (value < other.value)
			return -1;
		return 0;
	}

	bool Single::Equals(const Single other) const
	{
		return (value == other.value);
	}

	int Single::GetHashCode() const
	{
		return (int)value;
	}

	float Single::Parse(char *str)
	{
		float retval;
		char sign = 0;
		char *sp = str;

		if (*sp == '+' || *sp == '-')
        sign = *sp++;

		if (stricmp(sp, "inf") == 0)
		{
			if (!sign || sign == '+')
				retval = PositiveInfinity;
			else
				retval = NegativeInfinity;
		}
		else if (stricmp(sp, "nan") == 0)
			retval = NaN;
		else /* valid number */
			retval = (float)atof(sp);

		return retval;
	}

	const char* Single::ToString() const
	{
		return String::Format("%f", value);
	}

	bool Single::operator !=(float right) const
	{
		return (value != right);
	}

	bool Single::operator !=(const Single right) const
	{
		return (value != right.value);
	}

	bool Single::operator ==(float right) const
	{
		return (value == right);
	}

	bool Single::operator ==(const Single right) const
	{
		return (value == right.value);
	}
}
