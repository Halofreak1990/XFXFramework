// Copyright (C) XFX Team
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

#include <System/UInt32.h>
#include <System/String.h>

#include <stdlib.h>

namespace System
{
	const uint UInt32::MaxValue = 0xFFFFFFFF;
	const uint UInt32::MinValue = 0;

	UInt32::UInt32(const UInt32 &obj)
		: value(obj.value)
	{
	}

	UInt32::UInt32(const uint &obj)
		: value(obj)
	{
	}

	int UInt32::CompareTo(const UInt32 other) const
	{
		if (value > other.value)
			return 1;
		if (value < other.value)
			return -1;
		return 0;
	}

	bool UInt32::Equals(Object const * const obj) const
	{
		return is(this, obj) ? *this == *(UInt32 *)obj : false;
	}

	bool UInt32::Equals(const UInt32 other) const
	{
		return (*this == other);
	}

	int UInt32::GetHashCode() const
	{
		return (int)value;
	}

	int UInt32::GetType() const
	{
		return 10;
	}

	const String& UInt32::ToString() const
	{
		return String::Format("%i", value);
	}

	const String& UInt32::ToString(const uint value)
	{
		return String::Format("%i", value);
	}

	bool UInt32::TryParse(const char* str, out uint* result)
	{
		*result = 0;
		char* end = NULL;

		if (String::IsNullOrEmpty(str))
			return false;

		uint retval = strtoul(str, &end, 10);

		if (*end)
			return false;

		*result = retval;
		return true;
	}

	bool UInt32::operator==(const UInt32& right) const
	{
		return (value == right.value);
	}

	bool UInt32::operator==(const uint& right) const
	{
		return (value == right);
	}

	bool UInt32::operator!=(const UInt32& right) const
	{
		return (value != right.value);
	}

	bool UInt32::operator!=(const uint& right) const
	{
		return (value != right);
	}
}
