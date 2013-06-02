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

#include <System/Boolean.h>
#include <System/String.h>
#include <string.h>

namespace System
{
	const char* Boolean::TrueString = "True";
	const char* Boolean::FalseString = "False";

	Boolean::Boolean()
		: value(false)
	{
	}

	Boolean::Boolean(const Boolean &obj)
		: value(obj.value)
	{
	}

	Boolean::Boolean(const bool &obj)
		: value(obj)
	{
	}

	int Boolean::CompareTo(const Boolean other) const
	{
		if (value > other.value)
			return 1;
		if (value < other.value)
			return -1;
		return 0;
	}

	bool Boolean::Equals(Object const * const obj) const
	{
		return (obj != null && is(this, obj)) ? *this == *(Boolean *)obj : false;
	}

	bool Boolean::Equals(const Boolean other) const
	{
		return (*this == other);
	}

	int Boolean::GetType() const
	{
		return 3;
	}

	bool Boolean::Parse(const String& str)
	{
		if (str.CompareTo("false") == 0)
			return false;
		if (str.CompareTo("true") == 0)
			return true;
		return -1;
	}

	const String& Boolean::ToString() const
	{
		if (value)
			return "true";
		return "false";
	}

	const String& Boolean::ToString(bool value)
	{
		if (value)
			return "true";
		return "false";
	}

	Boolean::operator bool() const
	{
		return value;
	}

	bool Boolean::operator !=(const Boolean& right) const
	{
		return (value != right.value);
	}

	bool Boolean::operator ==(const Boolean& right) const
	{
		return (value == right.value);
	}
}
