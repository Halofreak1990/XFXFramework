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

#include <System/Int32.h>
#include <System/String.h>
#include <System/Type.h>

#include <stdlib.h>

namespace System
{
	const int Int32::MaxValue = 0x7FFFFFFF;
	const int Int32::MinValue = 0x80000000;

	const Type Int32TypeInfo("Int32", "System::Int32", TypeCode::Int32);

	Int32::Int32()
		: value(0)
	{
	}

	Int32::Int32(const Int32 &obj)
		: value(obj.value)
	{
	}

	Int32::Int32(const int &obj)
		: value(obj)
	{
	}

	int Int32::CompareTo(const Int32 other) const
	{
		if (value > other.value)
			return 1;
		if (value < other.value)
			return -1;
		return 0;
	}

	bool Int32::Equals(Object const * const obj) const
	{
		return is(obj, this) ? *this == *(Int32 *)obj : false;
	}

	bool Int32::Equals(const Int32 other) const
	{
		return (*this == other);
	}

	int Int32::GetHashCode() const
	{
		return value;
	}

	const Type& Int32::GetType()
	{
		return Int32TypeInfo;
	}

	const String Int32::ToString() const
	{
		return String::Format("%i", value);
	}

	const String Int32::ToString(const int value)
	{
		return String::Format("%i", value);
	}

	bool Int32::TryParse(const String& str, out int* result)
	{
		*result = 0;
		char* end = NULL;

		if (String::IsNullOrEmpty(str))
			return false;
		
		int  res = strtoul(str, &end, 10);

		if (*end)
		{
			return false;
		}
		
		*result = res;
		return true;
	}

	Int32::operator int() const
	{
		return value;
	}

	bool Int32::operator !=(const Int32& right) const
	{
		return (value != right.value);
	}

	bool Int32::operator ==(const Int32& right) const
	{
		return (value == right.value);
	}
}
