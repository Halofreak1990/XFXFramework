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

#include "Point.h"

namespace XFX
{
	const Point Point::Zero = Point(0, 0);
	
	Point::Point(int x, int y)
	{
		X = x;
		Y = y;
	}
	
	Point::Point(const Point &obj)
	{
		X = obj.X;
		Y = obj.Y;
	}
	
	Point::Point()
	{
		X = 0;
		Y = 0;
	}

	bool Point::Equals(Point other)
	{
		return ((X == other.X) && (Y == other.Y));
	}

	bool Point::operator==(const Point right)
	{
		return ((X == right.X) && (Y == right.Y));
	}

	bool Point::operator!=(const Point right)
	{
		return !((X == right.X) && (Y == right.Y));
	}
	
	Point Point::operator=(const Point right)
	{
		X = right.X;
		Y = right.Y;
		return *this;
	}
}
