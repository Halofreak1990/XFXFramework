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

#include <System/Int64.h>
#include <System/String.h>
#include <System/Type.h>

#include <stdlib.h>

namespace System
{
	const long long Int64::MaxValue = 0x7FFFFFFFFFFFFFFFLL;
	const long long Int64::MinValue = 0x8000000000000000LL;

	const Type Int64TypeInfo("Int64", "System::Int64", TypeCode::Int64);

	Int64::Int64()
		: value(0)
	{
	}

	Int64::Int64(const Int64 &obj)
		: value(obj.value)
	{
	}

	Int64::Int64(const long long &obj)
		: value(obj)
	{
	}

	int Int64::CompareTo(const Int64 other) const
	{
		if (value > other.value)
			return 1;
		if (value < other.value)
			return -1;
		return 0;
	}

	bool Int64::Equals(Object const * const obj) const
	{
		return is(obj, this) ? *this == *(Int64 *)obj : false;
	}

	bool Int64::Equals(const Int64 other) const
	{
		return (*this == other);
	}

	int Int64::GetHashCode() const
	{
		return (int)value;
	}

	const Type& Int64::GetType()
	{
		return Int64TypeInfo;
	}

	const String Int64::ToString() const
	{
		return String::Format("%lld", value);
	}

	const String Int64::ToString(const long long value)
	{
		return String::Format("%lld", value);
	}

	bool Int64::TryParse(const String& str, out long long* result)
	{
		*result = 0;
		char* end = NULL;

		if (String::IsNullOrEmpty(str))
		{
			return false;
		}

		long long retval = strtoll(str, &end, 10);

		if (end)
		{
			return false;
		}

		*result = retval;
		return true;
	}

	Int64::operator long long() const
	{
		return value;
	}

	bool Int64::operator==(const Int64& right) const
	{
		return (value == right.value);
	}

	bool Int64::operator!=(const Int64& right) const
	{
		return (value != right.value);
	}
}
