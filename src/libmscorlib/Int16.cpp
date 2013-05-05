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


#include <System/Int16.h>
#include <System/String.h>

#include <stdlib.h>

namespace System
{
	const short Int16::MaxValue = 0x7FFF;
	const short Int16::MinValue = 0x8000;

	Int16::Int16()
		: value(0)
	{
	}

	Int16::Int16(const Int16 &obj)
		: value(obj.value)
	{
	}

	Int16::Int16(const short &obj)
		: value(obj)
	{
	}

	int Int16::CompareTo(const Int16 other) const
	{
		if (value > other.value)
			return 1;
		if (value < other.value)
			return -1;
		return 0;
	}

	bool Int16::Equals(Object const * const obj) const
	{
		return is(obj, this) ? *this == *(Int16 *)obj : false;
	}

	bool Int16::Equals(const Int16 other) const
	{
		return (*this == other);
	}

	int Int16::GetHashCode() const
	{
		return value;
	}

	int Int16::GetType() const
	{
		return 7;
	}

	const char* Int16::ToString() const
	{
		return String::Format("%i", value);
	}

	const char* Int16::ToString(const short value)
	{
		return String::Format("%i", value);
	}

	bool Int16::TryParse(const String& str, out short* result)
	{
		*result = 0;
		char* end = NULL;

		if (String::IsNullOrEmpty(str))
			return false;

		short retval = (short)strtol(str, &end, 10);

		if (end)
			return false;

		*result = retval;
		return true;
	}

	Int16::operator short() const
	{
		return value;
	}

	bool Int16::operator==(const Int16& right) const
	{
		return (value == right.value);
	}

	bool Int16::operator==(const short& right) const
	{
		return (value == right);
	}

	bool Int16::operator!=(const Int16& right) const
	{
		return (value != right.value);
	}

	bool Int16::operator!=(const short& right) const
	{
		return (value != right);
	}
}
