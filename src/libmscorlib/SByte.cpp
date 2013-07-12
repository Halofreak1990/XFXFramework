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

#include <System/SByte.h>
#include <System/String.h>
#include <System/Type.h>

#include <stdlib.h>

namespace System
{
	const sbyte SByte::MaxValue = 127;
	const sbyte SByte::MinValue = -128;

	const Type SByteTypeInfo("SByte", "System::SByte", TypeCode::SByte);

	SByte::SByte()
		: value(0)
	{
	}

	SByte::SByte(const SByte &obj)
		: value(obj.value)
	{
	}

	SByte::SByte(const sbyte &obj)
		: value(obj)
	{
	}

	int SByte::CompareTo(const SByte other) const
	{
		if (value < other.value)
			return -1;
		if (value > other.value)
			return 1;
		return 0;
	}

	bool SByte::Equals(Object const * const obj) const
	{
		return is(obj, this) ? *this == *(SByte *)obj : false;
	}

	bool SByte::Equals(const SByte other) const
	{
		return (*this == other);
	}

	int SByte::GetHashCode() const
	{
		return value;
	}

	const Type& SByte::GetType()
	{
		return SByteTypeInfo;
	}

	const String SByte::ToString() const
	{
		return String::Format("%i", value);
	}

	const String SByte::ToString(const sbyte value)
	{
		return String::Format("%i", value);
	}

	bool SByte::TryParse(const String& str, out sbyte* result)
	{
		*result = 0;
		char* end = NULL;

		if (String::IsNullOrEmpty(str))
			return false;

		sbyte retval = (sbyte)strtol(str, &end, 10);

		if (end)
			return false;

		*result = retval;
		return true;
	}

	SByte::operator sbyte() const
	{
		return value;
	}

	bool SByte::operator ==(const SByte& right) const
	{
		return (value == right.value);
	}

	bool SByte::operator !=(const SByte& right) const
	{
		return (value != right.value);
	}
}
