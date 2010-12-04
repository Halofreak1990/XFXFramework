/********************************************************
 *	Rectangle.h											*
 *														*
 *	XFX Rectangle definition file						*
 *	Copyright © XFX Team. All Rights Reserved			*
 ********************************************************/
#ifndef _XFX_RECTANGLE_
#define _XFX_RECTANGLE_

#include <System/Types.h>

namespace XFX
{
	struct Point;
	
	struct Rectangle
	{
	public:
		int Bottom();
		int Left();
		int Right();
		int Top();
		int X, Y;
		static const Rectangle Empty;
		int Width, Height;

		Rectangle(int x,int y,int width,int height);
		Rectangle(const Rectangle &obj);
		Rectangle();
		
		int Contains(int x, int y);
		int Contains(Point pt);
		void Contains(Point pt, out int result);
		int Contains(Rectangle other);
		void Contains(Rectangle other, out int result);
		int Equals(const Rectangle obj);
		int GetHashCode();
		void Inflate(int horizontalAmount, int verticalAmount);
		int Intersects(Rectangle other);
		void Intersects(Rectangle other, out int result);
		void Offset(int x, int y);
		void Offset(Point pt);
		
		int operator==(const Rectangle other);
		int operator!=(const Rectangle other);
		Rectangle &operator=(const Rectangle other);
	};
}

#endif //_RECTANGLE_
