// Copyright (C) 2010-2012, XFX Team
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

namespace XFX
{
	const Rectangle Rectangle::Empty = Rectangle(0, 0, 0, 0);
	
	Rectangle::Rectangle(int x, int y, int width, int height)
	{
		X = x;
		Y = y;
		Width = width;
		Height = height;
	}
	
	Rectangle::Rectangle(const Rectangle &obj)
	{
		X = obj.X;
		Y = obj.Y;
		Width = obj.Width;
		Height = obj.Height;
	}
	
	Rectangle::Rectangle()
	{
		X = 0;
		Y = 0;
		Width = 0;
		Height = 0;
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
	
	int Rectangle::Contains(int x, int y)
	{
		return ((x >= X) && (y >=Y) && (x <= Right()) && (y <= Bottom()));
	}
	
	int Rectangle::Contains(Point pt)
	{
		return ((pt.X >= X) && (pt.Y >=Y) && (pt.X <= Right()) && (pt.Y <= Bottom()));
	}
	
	void Rectangle::Contains(Point pt, out int result)
	{
		result = ((pt.X >= X) && (pt.Y >=Y) && (pt.X <= Right()) && (pt.Y <= Bottom()));
	}
	
	int Rectangle::Contains(Rectangle other)
	{
		return ((other.X >= X) && (other.Y >= Y) && (other.Bottom() <= Bottom()) && (other.Right() <= Right()));
	}
	
	void Rectangle::Contains(Rectangle other, out int result)
	{
		result = ((other.X >= X) && (other.Y >= Y) && (other.Bottom() <= Bottom()) && (other.Right() <= Right()));
	}
	
	int Rectangle::Equals(const Rectangle obj)
	{
		return ((X == obj.X) && (Y == obj.Y) && (Width == obj.Width) && (Height == obj.Height));
	}
	
	int Rectangle::GetHashCode()
	{
		return X ^ Y ^ Width ^ Height;
	}
	
	void Rectangle::Inflate(int horizontalAmount, int verticalAmount)
	{
		Width += horizontalAmount;
		Height += verticalAmount;
	}
	
	int Rectangle::Intersects(Rectangle other)
	{
		return ((Contains(other.Left(), other.Top())) || (Contains(other.Left(), other.Bottom())) || (Contains(other.Right(), other.Top())) || (Contains(other.Right(),other.Bottom())));
	}
	
	void Rectangle::Intersects(Rectangle other, out int result)
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
	
	int Rectangle::operator==(const Rectangle other)
	{
		return Equals(other);
	}
	
	int Rectangle::operator!=(const Rectangle other)
	{
		return !Equals(other);
	}
	
	Rectangle &Rectangle::operator=(const Rectangle other)
	{
		X = other.X;
		Y = other.Y;
		Width = other.Width;
		Height = other.Height;
		return *this;
	}
}
