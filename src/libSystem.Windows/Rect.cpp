#include <System/Windows/Rect.h>
#include <System/Windows/Point.h>
#include <System/Windows/Size.h>
#include <System/String.h>

namespace System
{
	namespace Windows
	{
		const Rect Rect::Empty = Rect();

		int Rect::getBottom() const
		{
			return (Y + Height);
		}

		int Rect::getLeft() const
		{
			return X;
		}

		int Rect::getRight() const
		{
			return (X + Width);
		}

		int Rect::getTop() const
		{
			return Y;
		}

		Rect::Rect()
			: Height(0), Width(0), X(0), Y(0)
		{
		}

		Rect::Rect(const int x, const int y, const int width, const int height)
			: Height(height), Width(width), X(x), Y(y)
		{
		}

		Rect::Rect(const Point point1, const Point point2)
			: Height(point2.Y - point1.Y), Width(point2.X - point1.X), X(point1.X), Y(point1.Y)
		{
		}

		Rect::Rect(const Point location, const Size size)
			: Height(size.Height), Width(size.Width), X(location.X), Y(location.Y)
		{
		}

		Rect::Rect(const Rect &obj)
			: Height(obj.Height), Width(obj.Width), X(obj.X), Y(obj.Y)
		{
		}

		bool Rect::Contains(const Point point) const
		{
			return ((point.X >= X) && (point.X <= getRight()) &&
					(point.Y >= Y) && (point.Y <= getBottom()));
		}

		bool Rect::Equals(const Object* obj) const
		{
			return is(obj, this) ? this->Equals(*(Rect*)obj) : false;
		}

		bool Rect::Equals(const Rect other) const
		{
			return (*this == other);
		}

		int Rect::GetHashCode() const
		{
		}

		int Rect::GetType() const
		{
		}

		void Rect::Intersect(const Rect rect)
		{
		}

		const char* Rect::ToString() const
		{
			return String::Format("X:%i Y:%i Width:%i Height:%i", X, Y, Width, Height);
		}

		void Rect::Union(const Point point)
		{
			if (point.X < X)
			{
				int difference = (X - point.X);
				X -= difference;
				Width += difference;
			}
			if (point.X > getRight())
			{
				Width += (point.X - getRight());
			}
			if (point.Y < Y)
			{
				int difference = (Y - point.Y);
				Y -= difference;
				Height += difference;
			}
			if (point.Y > getBottom())
			{
				Height += (point.Y - getBottom());
			}
		}

		void Rect::Union(const Rect rect)
		{
		}

		bool Rect::operator ==(const Rect& right) const
		{
			return ((X == right.X) && (Y == right.Y) &&
					(Width == right.Width) && (Height == right.Height));
		}

		bool Rect::operator !=(const Rect& right) const
		{
			return !((X == right.X) && (Y == right.Y) &&
					(Width == right.Width) && (Height == right.Height));
		}
	}
}
