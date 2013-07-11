#ifndef _SYSTEM_WINDOWS_POINT_
#define _SYSTEM_WINDOWS_POINT_

#include <System/Interfaces.h>

namespace System
{
	namespace Windows
	{
		// Represents an x- and y-coordinate pair in two-dimensional space. Can also represent a logical point for certain property usages.
		struct Point : IEquatable<Point>, Object
		{
		public:
			int X;
			int Y;

			Point();
			Point(int x, int y);
			Point(const Point &obj);

			bool Equals(Object const * const obj) const;
			bool Equals(const Point other) const;
			int GetHashCode() const;
			static int GetType();
			const String& ToString() const;

			bool operator==(const Point& right) const;
			bool operator!=(const Point& right) const;
		};
	}
}

#endif // _SYSTEM_WINDOWS_POINT_
