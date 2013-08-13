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

#include <Point.h>
#include <Rectangle.h>
#include <System/Type.h>

namespace XFX
{
	const Rectangle Rectangle::Empty = Rectangle(0, 0, 0, 0);
	const Type RectangleTypeInfo("Rectangle", "XFX::Rectangle", TypeCode::Object);
	
	Rectangle::Rectangle(const int x, const int y, const int width, const int height)
		: Height(height), Width(width), X(x), Y(y)
	{
	}
	
	Rectangle::Rectangle(const Rectangle &obj)
		: Height(obj.Height), Width(obj.Width), X(obj.X), Y(obj.Y)
	{
	}
	
	Rectangle::Rectangle()
		: Height(0), Width(0), X(0), Y(0)
	{
	}
	
	int Rectangle::Bottom()
	{
		return Y + Height;
	}
	
	int Rectangle::Left()
	{
		return X;
	}
	
	int Rectangle::Right()
	{
		return X + Width;
	}
	
	int Rectangle::Top()
	{
		return Y;
	}
	
	bool Rectangle::Contains(int x, int y)
	{
		return ((x >= X) && (y >=Y) && (x <= Right()) && (y <= Bottom()));
	}
	
	bool Rectangle::Contains(Point pt)
	{
		return ((pt.X >= X) && (pt.Y >=Y) && (pt.X <= Right()) && (pt.Y <= Bottom()));
	}
	
	void Rectangle::Contains(Point pt, out bool& result)
	{
		result = ((pt.X >= X) && (pt.Y >=Y) && (pt.X <= Right()) && (pt.Y <= Bottom()));
	}
	
	bool Rectangle::Contains(Rectangle other)
	{
		return ((other.X >= X) && (other.Y >= Y) && (other.Bottom() <= Bottom()) && (other.Right() <= Right()));
	}
	
	void Rectangle::Contains(Rectangle other, out bool& result)
	{
		result = ((other.X >= X) && (other.Y >= Y) && (other.Bottom() <= Bottom()) && (other.Right() <= Right()));
	}
	
	bool Rectangle::Equals(Object const * const obj) const
	{
		return is(this, obj) ? *this == *(Rectangle *)obj : false;
	}

	bool Rectangle::Equals(const Rectangle obj) const
	{
		return (*this == obj);
	}
	
	int Rectangle::GetHashCode() const
	{
		return X ^ Y ^ Width ^ Height;
	}

	const Type& Rectangle::GetType()
	{
		return RectangleTypeInfo;
	}
	
	void Rectangle::Inflate(int horizontalAmount, int verticalAmount)
	{
		Width += horizontalAmount;
		Height += verticalAmount;
	}
	
	bool Rectangle::Intersects(Rectangle other)
	{
		return ((Contains(other.Left(), other.Top())) || (Contains(other.Left(), other.Bottom())) || (Contains(other.Right(), other.Top())) || (Contains(other.Right(),other.Bottom())));
	}
	
	void Rectangle::Intersects(Rectangle other, out bool& result)
	{
		result = Intersects(other);
	}
	
	void Rectangle::Offset(int x, int y)
	{
		X += x;
		Y += y;
	}
	
	void Rectangle::Offset(Point pt)
	{
		X += pt.X;
		Y += pt.Y;
	}
	
	bool Rectangle::operator==(const Rectangle& other) const
	{
		return ((X == other.X) && (Y == other.Y) && (Width == other.Width) && (Height == other.Height));
	}
	
	bool Rectangle::operator!=(const Rectangle& other) const
	{
		return ((X != other.X) || (Y != other.Y) || (Width != other.Width) || (Height != other.Height));
	}
}
