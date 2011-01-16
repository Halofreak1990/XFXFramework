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
		int Bottom();	//Returns the y-coordinate of the bottom of the rectangle.
		static const Rectangle Empty; //Returns a Rectangle with all of its values set to zero.
		int Left();		//Returns the x-coordinate of the left side of the rectangle.
		int Right();	//Returns the x-coordinate of the right side of the rectangle.
		int Top();		//Returns the y-coordinate of the top of the rectangle.
		int Height;		//Specifies the height of the rectangle.
		int Width;		//Specifies the width of the rectangle.
		int X;			//Specifies the x-coordinate of the rectangle.
		int Y;			//Specifies the y-coordinate of the rectangle.

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
		Rectangle operator=(const Rectangle other);
	};
}

#endif //_RECTANGLE_
