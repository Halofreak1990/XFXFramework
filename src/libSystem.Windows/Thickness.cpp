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

#include <System/Windows/Thickness.h>
#include <System/String.h>
#include <System/Type.h>

namespace System
{
	namespace Windows
	{
		const Type ThicknessTypeInfo("Thickness", "System::Windows::Thickness", TypeCode::Object);

		Thickness::Thickness()
			: Bottom(0), Left(0), Right(0), Top(0)
		{
		}

		Thickness::Thickness(const int uniformLength)
			: Bottom(uniformLength), Left(uniformLength), Right(uniformLength), Top(uniformLength)
		{
		}

		Thickness::Thickness(const int left, const int right, const int top, const int bottom)
			: Bottom(bottom), Left(left), Right(right), Top(top)
		{
		}

		Thickness::Thickness(const Thickness &obj)
			: Bottom(obj.Bottom), Left(obj.Left), Right(obj.Right), Top(obj.Top)
		{
		}

		bool Thickness::Equals(Object const * const obj) const
		{
			return is(obj, this) ? *this == *(Thickness*)obj : false;
		}

		bool Thickness::Equals(const Thickness other) const
		{
			return (*this == other);
		}

		int Thickness::GetHashCode() const
		{
			return (Left + Right + Top + Bottom);
		}

		const Type& Thickness::GetType()
		{
			return ThicknessTypeInfo;
		}

		const String Thickness::ToString() const
		{
			return String::Format("{Left:%i Right:%i Top:%i Bottom:%i}", Left, Right, Top, Bottom);
		}

		bool Thickness::operator==(const Thickness& right) const
		{
			return ((Left == right.Left) && (Right == right.Right) &&
					(Top == right.Top) && (Bottom == right.Bottom));
		}

		bool Thickness::operator!=(const Thickness& right) const
		{
			return ((Left != right.Left) || (Right != right.Right) ||
					(Top != right.Top) || (Bottom != right.Bottom));
		}
	}
}
