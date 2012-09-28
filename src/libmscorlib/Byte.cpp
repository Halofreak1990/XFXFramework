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

#include <System/Byte.h>
#include <System/String.h>
#include <stdlib.h>

namespace System
{
	const byte Byte::MaxValue = 255;
	const byte Byte::MinValue = 0;

	byte Byte::getValue() const
	{
		return value;
	}

	Byte::Byte(const Byte &obj)
		: value(obj.value)
	{
	}

	Byte::Byte(const byte &obj)
		: value(obj)
	{
	}

	int Byte::CompareTo(const Byte other) const
	{
		if (value > other.value)
			return 1;
		if (value < other.value)
			return -1;
		return 0;
	}

	bool Byte::Equals(const Byte other) const
	{
		return (value == other.value);
	}

	int Byte::GetType() const
	{
		return 6;
	}

	const char* Byte::ToString() const
	{
		return String::Format("%i", value);
	}

	const char* Byte::ToString(byte value)
	{
		return String::Format("%i", value);
	}

	bool Byte::TryParse(const String& str, out byte result)
	{
		result = 0;
		char* end = NULL;

		if (String::IsNullOrEmpty(str))
			return false;

		uint res = strtoul(str.ToString(), &end, 10);

		if (*end)
		{
			return false;
		}
		
		result = (byte)res;
		return true;
	}

	bool Byte::operator !=(const Byte right) const
	{
		return (value != right.value);
	}

	bool Byte::operator ==(const Byte right) const
	{
		return (value == right.value);
	}
}
