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

namespace System
{
	const byte Byte::MaxValue = 255;
	const byte Byte::MinValue = 0;

	Byte::Byte(byte b)
	{
		value = b;
	}

	int Byte::CompareTo(Byte other)
	{
		if (value > other.value)
			return 1;
		if (value < other.value)
			return -1;
		return 0;
	}

	bool Byte::Equals(Byte other)
	{
		return (value == other.value);
	}

	char* Byte::ToString()
	{
		return String::Format("%i", value);
	}

	char* Byte::ToString(byte value)
	{
		return String::Format("%i", value);
	}

	bool Byte::operator !=(byte right)
	{
		return (value != right);
	}

	bool Byte::operator !=(Byte right)
	{
		return (value != right.value);
	}

	bool Byte::operator ==(byte right)
	{
		return (value == right);
	}

	bool Byte::operator ==(Byte right)
	{
		return (value == right.value);
	}
}
