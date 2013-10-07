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

#include <System/Windows/Rect.h>
#include <System/Windows/Point.h>
#include <System/Windows/Size.h>
#include <System/String.h>
#include <System/Type.h>

namespace System
{
	namespace Windows
	{
		const Rect Rect::Empty = Rect();
		const Type RectTypeInfo("Rect", "System::Windows::Rect", TypeCode::Object);

		int Rect::getBottom() const
		{
			return (Y + Height);
		}

		int Rect::getLeft() const
		{
			return X;
		}

		int Rect::getRight() const
		{
			return (X + Width);
		}

		int Rect::getTop() const
		{
			return Y;
		}

		Rect::Rect()
			: Height(0), Width(0), X(0), Y(0)
		{
		}

		Rect::Rect(const int x, const int y, const int width, const int height)
			: Height(height), Width(width), X(x), Y(y)
		{
		}

		Rect::Rect(const Point point1, const Point point2)
			: Height(point2.Y - point1.Y), Width(point2.X - point1.X), X(point1.X), Y(point1.Y)
		{
		}

		Rect::Rect(const Point location, const Size size)
			: Height(size.Height), Width(size.Width), X(location.X), Y(location.Y)
		{
		}

		Rect::Rect(const Rect &obj)
			: Height(obj.Height), Width(obj.Width), X(obj.X), Y(obj.Y)
		{
		}

		bool Rect::Contains(const Point point) const
		{
			return ((point.X >= X) && (point.X <= getRight()) &&
					(point.Y >= Y) && (point.Y <= getBottom()));
		}

		bool Rect::Equals(Object const * const obj) const
		{
			return is(obj, this) ? this->Equals(*(Rect *)obj) : false;
		}

		bool Rect::Equals(const Rect other) const
		{
			return (*this == other);
		}

		int Rect::GetHashCode() const
		{
			// TODO: implement
		}

		const Type& Rect::GetType()
		{
			return RectTypeInfo;
		}

		void Rect::Intersect(const Rect rect)
		{
			// TODO: implement
		}

		const String Rect::ToString() const
		{
			return String::Format("X:%i Y:%i Width:%i Height:%i", X, Y, Width, Height);
		}

		void Rect::Union(const Point point)
		{
			if (point.X < X)
			{
				int difference = (X - point.X);
				X -= difference;
				Width += difference;
			}
			if (point.X > getRight())
			{
				Width += (point.X - getRight());
			}
			if (point.Y < Y)
			{
				int difference = (Y - point.Y);
				Y -= difference;
				Height += difference;
			}
			if (point.Y > getBottom())
			{
				Height += (point.Y - getBottom());
			}
		}

		void Rect::Union(const Rect rect)
		{
			// TODO: implement
		}

		bool Rect::operator ==(const Rect& right) const
		{
			return ((X == right.X) && (Y == right.Y) &&
					(Width == right.Width) && (Height == right.Height));
		}

		bool Rect::operator !=(const Rect& right) const
		{
			return !((X == right.X) && (Y == right.Y) &&
					(Width == right.Width) && (Height == right.Height));
		}
	}
}
