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

#include <System/Windows/Size.h>
#include <System/String.h>
#include <System/Type.h>

namespace System
{
	namespace Windows
	{
		const Size Size::Empty = Size();
		const Type SizeTypeInfo("Size", "System::Windows::Size", TypeCode::Object);

		Size::Size()
			: Height(0), Width(0)
		{
		}

		Size::Size(const int width, const int height)
			: Height(height), Width(width)
		{
		}

		Size::Size(const Size &obj)
			: Height(obj.Height), Width(obj.Width)
		{
		}

		bool Size::IsEmpty() const
		{
			return ((Width == 0) && (Height == 0));
		}

		bool Size::Equals(Object const * const obj) const
		{
			return is(obj, this) ? *this == *(Size*)obj : false;
		}

		bool Size::Equals(const Size other) const
		{
			return (*this == other);
		}

		int Size::GetHashCode() const
		{
			return Width ^ Height;
		}

		const Type& Size::GetType()
		{
			return SizeTypeInfo;
		}

		const String Size::ToString() const
		{
			return String::Format("{Width:%i Height:%i}", Width, Height);
		}

		bool Size::operator==(const Size& right) const
		{
			return ((Width == right.Width) && (Height == right.Height));
		}

		bool Size::operator!=(const Size& right) const
		{
			return ((Width != right.Width) || (Height != right.Height));
		}
	}
}
