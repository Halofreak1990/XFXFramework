#pragma once

#include <System/Interfaces.h>

namespace System
{
	namespace Windows
	{
		struct Point;
		struct Size;

		// Describes the width, height, and point origin of a rectangle.
		struct Rect : IEquatable<Rect>, Object
		{
		public:
			int getBottom() const;
			static const Rect Empty;
			int Height;
			int getLeft() const;
			int getRight() const;
			int getTop() const;
			int Width;
			int X;
			int Y;

			Rect();
			Rect(const int x, const int y, const int width, const int height);
			Rect(const Point point1, const Point point2);
			Rect(const Point location, const Size size);
			Rect(const Rect &obj);

			bool Contains(const Point point) const;
			bool Equals(const Object* obj) const;
			bool Equals(const Rect other) const;
			int GetHashCode() const;
			int GetType() const;
			void Intersect(const Rect rect);
			const char* ToString() const;
			void Union(const Point point);
			void Union(const Rect rect);
		};
	}
}
