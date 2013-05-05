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

			bool Equals(const Object* obj) const;
			bool Equals(const Point other) const;
			int GetHashCode() const;
			int GetType() const;
			const char* ToString() const;

			bool operator==(const Point& right) const;
			bool operator!=(const Point& right) const;
		};
	}
}
