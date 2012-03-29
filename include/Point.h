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
		int X;
		int Y;
		static const Point Zero;

		Point(const int x, const int y);
		Point(const Point &obj);
		Point();
		
		bool Equals(const Point other) const;
		int GetHashCode() const;
		const char* ToString() const;

		bool operator==(const Point right) const;
		bool operator!=(const Point right) const;
	};
}

#endif //_XFX_POINT_
