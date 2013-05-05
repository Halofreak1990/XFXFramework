#pragma once

#include <System/Interfaces.h>

namespace System
{
	namespace Windows
	{
		class SystemColors;

		namespace Media
		{
			// Describes a color in terms of alpha, red, green, and blue channels.
			struct Color : IEquatable<Color>, Object
			{
			private:
				uint packedValue;

				Color(uint packedValue);

				friend class SystemColors;

			public:
				static const Color Black;
				static const Color Blue;
				static const Color CornflowerBlue;
				static const Color DarkGray;
				static const Color GoldenRod;
				static const Color Green;
				static const Color Gray;
				static const Color LightGray;
				static const Color Magenta;
				static const Color Maroon;
				static const Color Red;
				static const Color Salmon;
				static const Color Transparent;
				static const Color White;

				byte A() const;
				byte B() const;
				byte G() const;
				byte R() const;

				bool Equals(const Object* obj) const;
				bool Equals(const Color other) const;
				static Color FromARGB(byte alpha, byte red, byte green, byte blue);
				int GetHashCode() const;
				int GetType() const;
				const char* ToString() const;

				bool operator==(const Color& right) const;
				bool operator!=(const Color& right) const;
			};
		}
	}
}
