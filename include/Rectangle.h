/*****************************************************************************
 *	Rectangle.h																 *
 *																			 *
 *	XFX Rectangle definition file											 *
 *	Copyright (c) XFX Team. All Rights Reserved 							 *
 *****************************************************************************/
#ifndef _XFX_RECTANGLE_
#define _XFX_RECTANGLE_

#include <System/Interfaces.h>
#include <System/Types.h>

using namespace System;

namespace XFX
{
	struct Point;
	
	// Defines a rectangle.
	struct Rectangle : IEquatable<Rectangle>, Object
	{
		int Bottom();	//Returns the y-coordinate of the bottom of the rectangle.
		static const Rectangle Empty; //Returns a Rectangle with all of its values set to zero.
		int Left();		//Returns the x-coordinate of the left side of the rectangle.
		int Right();	//Returns the x-coordinate of the right side of the rectangle.
		int Top();		//Returns the y-coordinate of the top of the rectangle.
		int Height;		//Specifies the height of the rectangle.
		int Width;		//Specifies the width of the rectangle.
		int X;			//Specifies the x-coordinate of the rectangle.
		int Y;			//Specifies the y-coordinate of the rectangle.

		Rectangle(const int x, const int y, const int width, const int height);
		Rectangle(const Rectangle &obj);
		Rectangle();
		
		bool Contains(int x, int y);
		bool Contains(Point pt);
		void Contains(Point pt, out bool& result);
		bool Contains(Rectangle other);
		void Contains(Rectangle other, out bool& result);
		bool Equals(Object const * const obj) const;
		bool Equals(const Rectangle obj) const;
		int GetHashCode() const;
		static int GetType();
		void Inflate(int horizontalAmount, int verticalAmount);
		bool Intersects(Rectangle other);
		void Intersects(Rectangle other, out bool& result);
		void Offset(int x, int y);
		void Offset(Point pt);
		const char* ToString();
		
		bool operator==(const Rectangle& other) const;
		bool operator!=(const Rectangle& other) const;
	};
}

#endif //_RECTANGLE_
