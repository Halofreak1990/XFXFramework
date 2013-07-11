#include <System/Windows/Point.h>
#include <System/String.h>

namespace System
{
	namespace Windows
	{
		Point::Point()
			: X(0), Y(0)
		{
		}

		Point::Point(const int x, const int y)
			: X(x), Y(y)
		{
		}

		Point::Point(const Point &obj)
			: X(obj.X), Y(obj.Y)
		{
		}

		bool Point::Equals(Object const * const obj) const
		{
			return is(obj, this) ? *this == *(Point*)obj : false;
		}

		bool Point::Equals(const Point other) const
		{
			return (*this == other);
		}

		int Point::GetHashCode() const
		{
			return X + Y;
		}

		int Point::GetType()
		{
			// TODO: implement
		}

		const String Point::ToString() const
		{
			return String::Format("{X:%i Y:%i}", X, Y);
		}

		bool Point::operator ==(const Point& right) const
		{
			return ((X == right.X) && (Y == right.Y));
		}

		bool Point::operator !=(const Point& right) const
		{
			return ((X != right.X) || (Y != right.Y));
		}
	}
}
