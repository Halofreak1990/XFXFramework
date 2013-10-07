// Copyright (C) XFX Team
// All rights reserved.
// 
// Redistribution and use in source and binary forms, with or without 
// modification, are permitted provided that the following conditions are met:
// 
//     * Redistributions of source code must retain the above copyright 
//       notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above copyright 
//       notice, this list of conditions and the following disclaimer in the 
//       documentation and/or other materials provided with the distribution.
//     * Neither the name of the copyright holder nor the names of any 
//       contributors may be used to endorse or promote products derived from 
//       this software without specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE 
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE 
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR 
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF 
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS 
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN 
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE 
// POSSIBILITY OF SUCH DAMAGE.

#include <System/Windows/Media/Color.h>
#include <System/String.h>
#include <System/Type.h>

namespace System
{
	namespace Windows
	{
		namespace Media
		{
			const Type ColorTypeInfo("Color", "System::Windows::Media::Color", TypeCode::Object);

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
				return is(obj, this) ? *this == *(Color *)obj : false;
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

			const Type& Color::GetType()
			{
				return ColorTypeInfo;
			}

			const String Color::ToString() const
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
