#pragma once

#include <System/Interfaces.h>

namespace System
{
	namespace Windows
	{
		// Describes the thickness of a frame around a rectangle.
		// Four int values describe the System::Windows::Thickness::Left,
		// System::Windows::Thickness.Top, System::Windows::Thickness.Right,
		// and System::Windows::Thickness.Bottom sides of the rectangle, respectively.
		struct Thickness : IEquatable<Thickness>, Object
		{
		public:
			int Bottom;
			int Left;
			int Right;
			int Top;

			Thickness();
			// Initializes a System::Windows::Thickness structure that has the specified uniform length on each side.
			Thickness(const int uniformLength);
			// Initializes a System::Windows::Thickness structure that has specific lengths (supplied as an int) applied to each side of the rectangle.
			Thickness(const int left, const int right, const int top, const int bottom);
			Thickness(const Thickness &obj);

			// Compares this System::Windows::Thickness structure to the specified System::Object for equality.
			bool Equals(const Object* obj) const;
			// Compares this System::Windows::Thickness structure to another System::Windows::Thickness structure for equality.
			bool Equals(const Thickness other) const;
			// Returns the hash code of the structure.
			int GetHashCode() const;
			// Returns the TypeCode for this object as an integer.
			int GetType() const;
			// Returns the string representation of the System::Windows::Thickness structure.
			const char* ToString() const;

			bool operator ==(const Thickness& right) const;
			bool operator !=(const Thickness& right) const;
		};
	}
}
