#include <System/Windows/Media/Color.h>
#include <System/String.h>

namespace System
{
	namespace Windows
	{
		namespace Media
		{
			Color::Color(uint packedValue)
				: packedValue(packedValue)
			{
			}

			byte Color::A() const
			{
				return (byte)(packedValue >> 24);
			}

			unsigned char Color::B() const
			{
				return (byte)packedValue;
			}

			byte Color::G() const
			{
				return (byte)(packedValue >> 8);
			}

			byte Color::R() const
			{
				return (byte)(packedValue >> 16);
			}

			bool Color::Equals(Object const * const obj) const
			{
				return is(obj, this) ? *this == *(Color*)obj : false;
			}

			bool Color::Equals(const Color other) const
			{
				return (*this == other);
			}

			Color Color::FromARGB(byte alpha, byte red, byte green, byte blue)
			{
				return Color(((alpha << 24) | (red << 16) | (green << 8) | blue));
			}

			int Color::GetHashCode() const
			{
				return (int)packedValue;
			}

			int Color::GetType() const
			{
			}

			const char* Color::ToString() const
			{
				return String::Format("#%08X", packedValue);
			}

			bool Color::operator==(const Color& right) const
			{
				return (packedValue == right.packedValue);
			}

			bool Color::operator!=(const Color& right) const
			{
				return (packedValue != right.packedValue);
			}

			///////////////////////////////////////////////////////////////////

			const Color Color::Black = Color(0xFF000000);
			const Color Color::Blue = Color(0xFF0000FF);
			const Color Color::CornflowerBlue = Color(0xFF6495ED);
			const Color Color::DarkGray = Color(0xFFA9A9A9);
			const Color Color::GoldenRod = Color(0xFFDAA520);
			const Color Color::Gray = Color(0xFF808080);
			const Color Color::Green = Color(0xFF008000);
			const Color Color::Magenta = Color(0xFFFF00FF);
			const Color Color::Maroon = Color(0xFF800000);
			const Color Color::Red = Color(0xFFFF0000);
			const Color Color::Salmon = Color(0xFFFA8072);
			const Color Color::Transparent = Color(0x00000000);
			const Color Color::White = Color(0xFFFFFFFF);
		}
	}
}
