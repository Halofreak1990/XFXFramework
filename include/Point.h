/********************************************************
 *	Point.h												*
 *														*
 *	XFX Point definition file							*
 *	Copyright © XFX Team. All Rights Reserved			*
 ********************************************************/
#ifndef _XFX_POINT_
#define _XFX_POINT_

#include <System/Interfaces.h>
#include <System/Object.h>

using namespace System;

namespace XFX
{
	struct Point : public IEquatable<Point>, virtual Object
	{
	public:
		int X;
		int Y;
		static const Point Zero;

		Point(int x, int y);
		Point(const Point &obj);
		Point();
		
		bool Equals(Point other);
		bool operator==(const Point right);
		bool operator!=(const Point right);
		Point operator=(const Point right);
	};
}

#endif //_XFX_POINT_
