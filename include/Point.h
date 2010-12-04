/********************************************************
 *	Point.h												*
 *														*
 *	XFX Point definition file							*
 *	Copyright © XFX Team. All Rights Reserved			*
 ********************************************************/
#ifndef _POINT_
#define _POINT_

#include <System.h>

namespace XFX
{
	class Point
	{
		public:
			int X;
			int Y;
			static const Point Zero;

			Point(int x, int y);
			Point(const Point &obj);
			Point();
			
			int Equals(const Point &obj);
			int operator==(const Point &other);
			int operator!=(const Point &other);
			Point &operator=(const Point &other);
	};
}

#endif //_POINT_
