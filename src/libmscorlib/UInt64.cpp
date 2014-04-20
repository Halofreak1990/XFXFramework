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

#include <System/UInt64.h>
#include <System/String.h>
#include <System/Type.h>

#undef __STRICT_ANSI__
#include <stdlib.h>

namespace System
{
	const ulong UInt64::MaxValue = 0xFFFFFFFFFFFFFFFFULL;
	const ulong UInt64::MinValue = 0;
	const Type UInt64TypeInfo("UInt64", "System::UInt64", TypeCode::UInt64);

	UInt64::UInt64(const UInt64 &obj)
		: value(obj.value)
	{
	}

	UInt64::UInt64(const ulong &obj)
		: value(obj)
	{
	}

	int UInt64::CompareTo(const UInt64 other) const
	{
		if (value > other.value)
		{
			return 1;
		}

		if (value < other.value)
		{
			return -1;
		}

		return 0;
	}

	bool UInt64::Equals(Object const * const obj) const
	{
		return (obj != null && is(obj, this)) ? (*this == *(UInt64 *)obj) : false;
	}

	bool UInt64::Equals(const UInt64 other) const
	{
		return (*this == other);
	}

	int UInt64::GetHashCode() const
	{
		return (int)value;
	}

	const Type& UInt64::GetType()
	{
		return UInt64TypeInfo;
	}

	const String UInt64::ToString() const
	{
		return String::Format("%ull", value);
	}

	const String UInt64::ToString(const ulong value)
	{
		return String::Format("%ull", value);
	}

	bool UInt64::TryParse(const String& str, out ulong* result)
	{
		*result = 0;
		char* end = NULL;

		if (String::IsNullOrEmpty(str))
		{
			return false;
		}

		ulong retval = strtoull(str, &end, 10);

		if (end)
		{
			return false;
		}

		*result = retval;
		return true;
	}

	UInt64::operator ulong() const
	{
		return value;
	}

	bool UInt64::operator==(const UInt64& right) const
	{
		return (value == right.value);
	}

	/*bool UInt64::operator==(const ulong& right) const
	{
		return (value == right);
	}*/

	bool UInt64::operator!=(const UInt64& right) const
	{
		return (value != right.value);
	}

	/*bool UInt64::operator!=(const ulong& right) const
	{
		return (value != right);
	}*/
}
