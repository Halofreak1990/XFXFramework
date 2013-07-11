/*****************************************************************************
 *	Point.h																	 *
 *																			 *
 *	XFX::Point structure definition file									 *
 *	Copyright (c) XFX Team. All Rights Reserved 							 *
 *****************************************************************************/
#ifndef _XFX_POINT_
#define _XFX_POINT_

#include <System/Interfaces.h>

using namespace System;

namespace XFX
{
	/**
	 * Defines a point in 2D space.
	 */
	struct Point : IEquatable<Point>, Object
	{
		int X;
		int Y;
		static const Point Zero;

		Point(const int x, const int y);
		Point(const Point &obj);
		Point();
		
		bool Equals(Object const * const obj) const;
		bool Equals(const Point other) const;
		int GetHashCode() const;
		static int GetType();
		const String ToString() const;

		bool operator==(const Point& right) const;
		bool operator!=(const Point& right) const;
	};
}

#endif //_XFX_POINT_
