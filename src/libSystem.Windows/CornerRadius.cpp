// Copyright (C) XFX Team
// All rights reserved.
// 
// Redistribution and use in source and binary forms, with or without 
// modification, are permitted provided that the following conditions are met:
// 
//* Redistributions of source code must retain the above copyright 
//notice, this list of conditions and the following disclaimer.
//* Redistributions in binary form must reproduce the above copyright 
//notice, this list of conditions and the following disclaimer in the 
//documentation and/or other materials provided with the distribution.
//* Neither the name of the copyright holder nor the names of any 
//contributors may be used to endorse or promote products derived from 
//this software without specific prior written permission.
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

#include <System/Windows/CornerRadius.h>
#include <System/String.h>

namespace System
{
	namespace Windows
	{
		CornerRadius::CornerRadius()
			: BottomLeft(0), BottomRight(0), TopLeft(0), TopRight(0)
		{
		}

		CornerRadius::CornerRadius(const int uniformValue)
			: BottomLeft(uniformValue), BottomRight(uniformValue),
			TopLeft(uniformValue), TopRight(uniformValue)
		{
		}

		CornerRadius::CornerRadius(const int bottomLeft, const int bottomRight, const int topLeft, const int topRight)
			: BottomLeft(bottomLeft), BottomRight(bottomRight),
			TopLeft(topLeft), TopRight(topRight)
		{
		}
		
		CornerRadius::CornerRadius(const CornerRadius &obj)
			: BottomLeft(obj.BottomLeft), BottomRight(obj.BottomRight),
			TopLeft(obj.TopLeft), TopRight(obj.TopRight)
		{
		}

		bool CornerRadius::Equals(Object const * const obj) const
		{
			return is(obj, this) ? *this == *(CornerRadius*)obj : false;
		}

		bool CornerRadius::Equals(const CornerRadius other) const
		{
			return (*this == other);
		}

		int CornerRadius::GetHashCode() const
		{
			return (((TopLeft ^ TopRight) ^ BottomLeft) ^ BottomRight);
		}

		int CornerRadius::GetType()
		{
			// TODO: implement
		}

		const String CornerRadius::ToString() const
		{
			return String::Format("{BottomLeft:%i BottomRight:%i TopLeft:%i TopRight:%i}", BottomLeft, BottomRight, TopLeft, TopRight);
		}

		bool CornerRadius::operator==(const CornerRadius& right) const
		{
			return ((BottomLeft == right.BottomLeft) && (BottomRight == right.BottomRight) &&
					(TopLeft == right.TopLeft) && (TopRight == right.TopRight));
		}

		bool CornerRadius::operator!=(const CornerRadius& right) const
		{
			return ((BottomLeft != right.BottomLeft) || (BottomRight != right.BottomRight) ||
					(TopLeft != right.TopLeft) || (TopRight != right.TopRight));
		}
	}
}
