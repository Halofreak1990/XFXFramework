// Copyright (C) 2010-2012, XFX Team
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

#include <Graphics/Color.h>
#include <Vector3.h>
#include <Vector4.h>

using namespace XFX;

namespace XFX
{
	namespace Graphics
	{
		uint Color::RGBAtoARGB(uint value)
		{
			uint x = ((value >> 0) ^ (value >> 25)) & ((1U << 8) - 1); // XOR temporary
			return value ^ ((x << 0) | (x << 25));
		}
		
		/*** COLOR DEFINITIONS ***/
		const Color Color::AliceBlue = Color(((uint)255 << 24) + ((uint)240 << 16) + ((uint)248 << 8) + 255);
		const Color Color::AntiqueWhite = Color(((uint)255 << 24) + ((uint)250 << 16) + ((uint)235 << 8) + 215);
		const Color Color::Aqua = Color(((uint)255 << 24) + ((uint)0 << 16) + ((uint)255 << 8) + 255);
		const Color Color::AquaMarine = Color(((uint)255 << 24) + ((uint)127 << 16) + ((uint)255 << 8) + 212);
		const Color Color::Azure = Color(((uint)255 << 24) + ((uint)240 << 16) + ((uint)255 << 8) + 255);
		const Color Color::Beige = Color(((uint)255 << 24) + ((uint)245 << 16) + ((uint)245 << 8) + 220);
		const Color Color::Bisque = Color(((uint)255 << 24) + ((uint)255 << 16) + ((uint)228 << 8) + 196);
		const Color Color::Black = Color(((uint)255 << 24) + ((uint)0 << 16) + ((uint)0 << 8) + 0);
		const Color Color::BlanchedAlmond = Color(((uint)255 << 24) + ((uint)255 << 16) + ((uint)235 << 8) + 205); 
		const Color Color::Blue = Color(((uint)255 << 24) + ((uint)0 << 16) + ((uint)0 << 8) + 255);
		const Color Color::BlueViolet = Color(((uint)255 << 24) + ((uint)138 << 16) + ((uint)43 << 8) + 226);
		const Color Color::Brown = Color(((uint)255 << 24) + ((uint)165 << 16) + ((uint)42 << 8) + 42);
		const Color Color::BurlyWood = Color(((uint)255 << 24) + ((uint)222 << 16) + ((uint)184 << 8) + 135);
		const Color Color::CadetBlue = Color(((uint)255 << 24) + ((uint)95 << 16) + ((uint)158 << 8) + 160);
		const Color Color::Chartreuse = Color(((uint)255 << 24) + ((uint)127 << 16) + ((uint)255 << 8) + 0);
		const Color Color::Chocolate = Color(((uint)255 << 24) + ((uint)210 << 16) + ((uint)105 << 8) + 30);
		const Color Color::Coral = Color(((uint)255 << 24) + ((uint)255 << 16) + ((uint)127 << 8) + 80);
		const Color Color::CornflowerBlue = Color(((uint)255 << 24) + ((uint)100 << 16) + ((uint)149 << 8) + 237);
		const Color Color::Cornsilk = Color(((uint)255 << 24) + ((uint)255 << 16) + ((uint)248 << 8) + 220);
		const Color Color::Crimson = Color(((uint)255 << 24) + ((uint)220 << 16) + ((uint)20 << 8) + 60);
		const Color Color::Cyan = Color(((uint)255 << 24) + ((uint)0 << 16) + ((uint)255 << 8) + 255);
		const Color Color::DarkBlue = Color(((uint)255 << 24) + ((uint)0 << 16) + ((uint)0 << 8) + 139);
		const Color Color::DarkCyan = Color(((uint)255 << 24) + ((uint)0 << 16) + ((uint)139 << 8) + 139);
		const Color Color::DarkGoldenrod = Color(((uint)255 << 24) + ((uint)184 << 16) + ((uint)134 << 8) + 11);
		const Color Color::DarkGray = Color(((uint)255 << 24) + ((uint)169 << 16) + ((uint)169 << 8) + 169);
		const Color Color::DarkGreen = Color(((uint)255 << 24) + ((uint)0 << 16) + ((uint)100 << 8) + 0);
		const Color Color::DarkKhaki = Color(((uint)255 << 24) + ((uint)189 << 16) + ((uint)183 << 8) + 107);
		const Color Color::DarkMagenta = Color(((uint)255 << 24) + ((uint)139 << 16) + ((uint)0 << 8) + 139);
		const Color Color::DarkOliveGreen = Color(((uint)255 << 24) + ((uint)85 << 16) + ((uint)107 << 8) + 47);
		const Color Color::DarkOrange = Color(((uint)255 << 24) + ((uint)255 << 16) + ((uint)140 << 8) + 0);
		const Color Color::DarkOrchid = Color(((uint)255 << 24) + ((uint)153 << 16) + ((uint)50 << 8) + 204);
		const Color Color::DarkRed = Color(((uint)255 << 24) + ((uint)139 << 16) + ((uint)0 << 8) + 0);
		const Color Color::DarkSalmon = Color(((uint)255 << 24) + ((uint)233 << 16) + ((uint)150 << 8) + 122);
		const Color Color::DarkSeaGreen = Color(((uint)255 << 24) + ((uint)143 << 16) + ((uint)188 << 8) + 139);
		const Color Color::DarkSlateBlue = Color(((uint)255 << 24) + ((uint)72 << 16) + ((uint)61 << 8) + 139);
		const Color Color::DarkSlateGray = Color(((uint)255 << 24) + ((uint)47 << 16) + ((uint)79 << 8) + 79);
		const Color Color::DarkTurquoise = Color(((uint)255 << 24) + ((uint)0 << 16) + ((uint)206 << 8) + 209);
		const Color Color::DarkViolet = Color(((uint)255 << 24) + ((uint)148 << 16) + ((uint)0 << 8) + 211);
		const Color Color::DeepPink = Color(((uint)255 << 24) + ((uint)255 << 16) + ((uint)20 << 8) + 147);
		const Color Color::DeepSkyBlue = Color(((uint)255 << 24) + ((uint)0 << 16) + ((uint)191 << 8) + 255);
		const Color Color::DimGray = Color(((uint)255 << 24) + ((uint)105 << 16) + ((uint)105 << 8) + 105);
		const Color Color::DodgerBlue = Color(((uint)255 << 24) + ((uint)30 << 16) + ((uint)144 << 8) + 255);
		const Color Color::FireBrick = Color(((uint)255 << 24) + ((uint)178 << 16) + ((uint)34 << 8) + 34);
		const Color Color::FloralWhite = Color(((uint)255 << 24) + ((uint)255 << 16) + ((uint)250 << 8) + 240);
		const Color Color::ForestGreen = Color(((uint)255 << 24) + ((uint)34 << 16) + ((uint)139 << 8) + 34);
		const Color Color::Fuchsia = Color(((uint)255 << 24) + ((uint)255 << 16) + ((uint)0 << 8) + 255);
		const Color Color::Gainsboro = Color(((uint)255 << 24) + ((uint)220 << 16) + ((uint)220 << 8) + 220);
		const Color Color::GhostWhite = Color(((uint)255 << 24) + ((uint)248 << 16) + ((uint)248 << 8) + 255);
		const Color Color::Gold = Color(((uint)255 << 24) + ((uint)255 << 16) + ((uint)215 << 8) + 0);
		const Color Color::Goldenrod = Color(((uint)255 << 24) + ((uint)218 << 16) + ((uint)165 << 8) + 32);
		const Color Color::Gray = Color(((uint)255 << 24) + ((uint)128 << 16) + ((uint)128 << 8) + 128);
		const Color Color::Green = Color(((uint)255 << 24) + ((uint)0 << 16) + ((uint)128 << 8) + 0);
		const Color Color::GreenYellow = Color(((uint)255 << 24) + ((uint)173 << 16) + ((uint)255 << 8) + 47);
		const Color Color::Honeydew = Color(((uint)255 << 24) + ((uint)240 << 16) + ((uint)255 << 8) + 240);
		const Color Color::HotPink = Color(((uint)255 << 24) + ((uint)255 << 16) + ((uint)105 << 8) + 180);
		const Color Color::IndianRed = Color(((uint)255 << 24) + ((uint)205 << 16) + ((uint)92 << 8) + 92);
		const Color Color::Indigo = Color(((uint)255 << 24) + ((uint)75 << 16) + ((uint)0 << 8) + 130);
		const Color Color::Ivory = Color(((uint)255 << 24) + ((uint)255 << 16) + ((uint)255 << 8) + 240);
		const Color Color::Khaki = Color(((uint)255 << 24) + ((uint)240 << 16) + ((uint)230 << 8) + 140);
		const Color Color::Lavender = Color(((uint)255 << 24) + ((uint)230 << 16) + ((uint)230 << 8) + 250);
		const Color Color::LavenderBlush = Color(((uint)255 << 24) + ((uint)255 << 16) + ((uint)240 << 8) + 245);
		const Color Color::LawnGreen = Color(((uint)255 << 24) + ((uint)124 << 16) + ((uint)252 << 8) + 0);
		const Color Color::LemonChiffon = Color(((uint)255 << 24) + ((uint)255 << 16) + ((uint)250 << 8) + 205);
		const Color Color::LightBlue = Color(((uint)255 << 24) + ((uint)173 << 16) + ((uint)216 << 8) + 230);
		const Color Color::LightCoral = Color(((uint)255 << 24) + ((uint)240 << 16) + ((uint)128 << 8) + 128);
		const Color Color::LightCyan = Color(((uint)255 << 24) + ((uint)224 << 16) + ((uint)255 << 8) + 255);
		const Color Color::LightGoldenrodYellow = Color(((uint)255 << 24) + ((uint)250 << 16) + ((uint)250 << 8) + 210);
		const Color Color::LightGray = Color(((uint)255 << 24) + ((uint)211 << 16) + ((uint)211 << 8) + 211);
		const Color Color::LightGreen = Color(((uint)255 << 24) + ((uint)144 << 16) + ((uint)238 << 8) + 144);
		const Color Color::LightPink = Color(((uint)255 << 24) + ((uint)255 << 16) + ((uint)182 << 8) + 193);
		const Color Color::LightSalmon = Color(((uint)255 << 24) + ((uint)255 << 16) + ((uint)160 << 8) + 122);
		const Color Color::LightSeaGreen = Color(((uint)255 << 24) + ((uint)32 << 16) + ((uint)178 << 8) + 170);
		const Color Color::LightSkyBlue = Color(((uint)255 << 24) + ((uint)135 << 16) + ((uint)206 << 8) + 250);
		const Color Color::LightSlateGray = Color(((uint)255 << 24) + ((uint)119 << 16) + ((uint)136 << 8) + 153);
		const Color Color::LightSteelBlue = Color(((uint)255 << 24) + ((uint)176 << 16) + ((uint)196 << 8) + 222);
		const Color Color::LightYellow = Color(((uint)255 << 24) + ((uint)255 << 16) + ((uint)255 << 8) + 224);
		const Color Color::Lime = Color(((uint)255 << 24) + ((uint)0 << 16) + ((uint)255 << 8) + 0);
		const Color Color::LimeGreen = Color(((uint)255 << 24) + ((uint)50 << 16) + ((uint)205 << 8) + 50);
		const Color Color::Linen = Color(((uint)255 << 24) + ((uint)250 << 16) + ((uint)240 << 8) + 230);
		const Color Color::Magenta = Color(((uint)255 << 24) + ((uint)255 << 16) + ((uint)0 << 8) + 255);
		const Color Color::Maroon = Color(((uint)255 << 24) + ((uint)128 << 16) + ((uint)0 << 8) + 0);
		const Color Color::MediumAquamarine = Color(((uint)255 << 24) + ((uint)102 << 16) + ((uint)205 << 8) + 170);
		const Color Color::MediumBlue = Color(((uint)255 << 24) + ((uint)0 << 16) + ((uint)0 << 8) + 205);
		const Color Color::MediumOrchid = Color(((uint)255 << 24) + ((uint)186 << 16) + ((uint)85 << 8) + 211);
		const Color Color::MediumPurple = Color(((uint)255 << 24) + ((uint)147 << 16) + ((uint)112 << 8) + 219);
		const Color Color::MediumSeaGreen = Color(((uint)255 << 24) + ((uint)60 << 16) + ((uint)179 << 8) + 113);
		const Color Color::MediumSlateBlue = Color(((uint)255 << 24) + ((uint)123 << 16) + ((uint)104 << 8) + 238);
		const Color Color::MediumSpringGreen = Color(((uint)255 << 24) + ((uint)0 << 16) + ((uint)250 << 8) + 154);
		const Color Color::MediumTurquoise = Color(((uint)255 << 24) + ((uint)72 << 16) + ((uint)209 << 8) + 204);
		const Color Color::MediumVioletRed = Color(((uint)255 << 24) + ((uint)199 << 16) + ((uint)21 << 8) + 133);
		const Color Color::MidnightBlue = Color(((uint)255 << 24) + ((uint)25 << 16) + ((uint)25 << 8) + 112);
		const Color Color::MintCream = Color(((uint)255 << 24) + ((uint)245 << 16) + ((uint)255 << 8) + 250);
		const Color Color::MistyRose = Color(((uint)255 << 24) + ((uint)255 << 16) + ((uint)228 << 8) + 225);
		const Color Color::Moccasin = Color(((uint)255 << 24) + ((uint)255 << 16) + ((uint)228 << 8) + 181);
		const Color Color::NavajoWhite = Color(((uint)255 << 24) + ((uint)255 << 16) + ((uint)222 << 8) + 173);
		const Color Color::Navy = Color(((uint)255 << 24) + ((uint)0 << 16) + ((uint)0 << 8) + 128);
		const Color Color::OldLace = Color(((uint)255 << 24) + ((uint)253 << 16) + ((uint)245 << 8) + 230);
		const Color Color::Olive = Color(((uint)255 << 24) + ((uint)128 << 16) + ((uint)128 << 8) + 0);
		const Color Color::OliveDrab = Color(((uint)255 << 24) + ((uint)107 << 16) + ((uint)142 << 8) + 35);
		const Color Color::Orange = Color(((uint)255 << 24) + ((uint)255 << 16) + ((uint)165 << 8) + 0);
		const Color Color::OrangeRed = Color(((uint)255 << 24) + ((uint)255 << 16) + ((uint)69 << 8) + 0);
		const Color Color::Orchid = Color(((uint)255 << 24) + ((uint)218 << 16) + ((uint)112 << 8) + 214);
		const Color Color::PaleGoldenrod = Color(((uint)255 << 24) + ((uint)238 << 16) + ((uint)232 << 8) + 170);
		const Color Color::PaleGreen = Color(((uint)255 << 24) + ((uint)152 << 16) + ((uint)251 << 8) + 152);
		const Color Color::PaleTurquoise = Color(((uint)255 << 24) + ((uint)175 << 16) + ((uint)238 << 8) + 238);
		const Color Color::PaleVioletRed = Color(((uint)255 << 24) + ((uint)219 << 16) + ((uint)112 << 8) + 147);
		const Color Color::PapayaWhip = Color(((uint)255 << 24) + ((uint)255 << 16) + ((uint)239 << 8) + 213);
		const Color Color::PeachPuff = Color(((uint)255 << 24) + ((uint)255 << 16) + ((uint)218 << 8) + 185);
		const Color Color::Peru = Color(((uint)255 << 24) + ((uint)205 << 16) + ((uint)133 << 8) + 63);
		const Color Color::Pink = Color(((uint)255 << 24) + ((uint)255 << 16) + ((uint)192 << 8) + 203);
		const Color Color::Plum = Color(((uint)255 << 24) + ((uint)221 << 16) + ((uint)160 << 8) + 221);
		const Color Color::PowderBlue = Color(((uint)255 << 24) + ((uint)176 << 16) + ((uint)224 << 8) + 230);
		const Color Color::Purple = Color(((uint)255 << 24) + ((uint)128 << 16) + ((uint)0 << 8) + 128);
		const Color Color::Red = Color(((uint)255 << 24) + ((uint)255 << 16) + ((uint)0 << 8) + 0);
		const Color Color::RosyBrown = Color(((uint)255 << 24) + ((uint)188 << 16) + ((uint)143 << 8) + 143);
		const Color Color::RoyalBlue = Color(((uint)255 << 24) + ((uint)65 << 16) + ((uint)105 << 8) + 225);
		const Color Color::SaddleBrown = Color(((uint)255 << 24) + ((uint)139 << 16) + ((uint)69 << 8) + 19);
		const Color Color::Salmon = Color(((uint)255 << 24) + ((uint)250 << 16) + ((uint)128 << 8) + 114);
		const Color Color::SandyBrown = Color(((uint)255 << 24) + ((uint)244 << 16) + ((uint)164 << 8) + 96);
		const Color Color::SeaGreen = Color(((uint)255 << 24) + ((uint)46 << 16) + ((uint)139 << 8) + 87);
		const Color Color::SeaShell = Color(((uint)255 << 24) + ((uint)255 << 16) + ((uint)245 << 8) + 238);
		const Color Color::Sienna = Color(((uint)255 << 24) + ((uint)160 << 16) + ((uint)82 << 8) + 45);
		const Color Color::Silver = Color(((uint)255 << 24) + ((uint)192 << 16) + ((uint)192 << 8) + 192);
		const Color Color::SkyBlue = Color(((uint)255 << 24) + ((uint)135 << 16) + ((uint)206 << 8) + 235);
		const Color Color::SlateBlue = Color(((uint)255 << 24) + ((uint)106 << 16) + ((uint)90 << 8) + 205);
		const Color Color::SlateGray = Color(((uint)255 << 24) + ((uint)112 << 16) + ((uint)128 << 8) + 144);
		const Color Color::Snow = Color(((uint)255 << 24) + ((uint)255 << 16) + ((uint)250 << 8) + 250);
		const Color Color::SpringGreen = Color(((uint)255 << 24) + ((uint)0 << 16) + ((uint)255 << 8) + 127);
		const Color Color::SteelBlue = Color(((uint)255 << 24) + ((uint)70 << 16) + ((uint)130 << 8) + 180);
		const Color Color::Tan = Color(((uint)255 << 24) + ((uint)210 << 16) + ((uint)180 << 8) + 140);
		const Color Color::Teal = Color(((uint)255 << 24) + ((uint)0 << 16) + ((uint)128 << 8) + 128);
		const Color Color::Thistle = Color(((uint)255 << 24) + ((uint)216 << 16) + ((uint)191 << 8) + 216);
		const Color Color::Tomato = Color(((uint)255 << 24) + ((uint)255 << 16) + ((uint)99 << 8) + 71);
		const Color Color::Turquoise = Color(((uint)255 << 24) + ((uint)64 << 16) + ((uint)224 << 8) + 208);
		const Color Color::Violet = Color(((uint)255 << 24) + ((uint)238 << 16) + ((uint)130 << 8) + 238);
		const Color Color::Wheat = Color(((uint)255 << 24) + ((uint)245 << 16) + ((uint)222 << 8) + 179);
		const Color Color::White = Color(((uint)255 << 24) + ((uint)255 << 16) + ((uint)255 << 8) + 255);
		const Color Color::WhiteSmoke = Color(((uint)255 << 24) + ((uint)245 << 16) + ((uint)245 << 8) + 245);
		const Color Color::Yellow = Color(((uint)255 << 24) + ((uint)255 << 16) + ((uint)255 << 8) + 0);
		const Color Color::YellowGreen = Color(((uint)255 << 24) + ((uint)154 << 16) + ((uint)205 << 8) + 50);
		/*** END OF COLOR DEFINITIONS ***/
		
		byte Color::A()
		{
			return (uint)((_packedValue >> 24 & 0xff));
		}
		
		byte Color::B()
		{
			return (uint)(_packedValue & 0xff); 
		}
		
		byte Color::G()
		{
			return (uint)((_packedValue >> 8 & 0xff));
		}
		
		byte Color::R()
		{
			return (uint)((_packedValue >> 16 & 0xff));
		}
		
		Color::Color(uint packedValue)
		{
			_packedValue = packedValue;
		}
		
		Color::Color(Vector3 vector)
		{
			_packedValue = InitializeFromVector3(vector);
		}
		
		Color::Color(Vector4 vector)
		{
			_packedValue = InitializeFromVector4(vector);
		}
		
		Color::Color(byte r, byte g, byte b)
		{
			_packedValue = (uint)(255 << 24) + (uint)(r << 16) + (uint)(g << 8) + b;
		}
		
		Color::Color(byte r, byte g, byte b, byte a)
		{
			_packedValue = (uint)(a << 24) + (uint)(r << 16) + (uint)(g << 8) + b;
		}
		
		bool Color::Equals(Color other)
		{
			return (_packedValue == other._packedValue);
		}
		
		int Color::GetHashCode()
		{
			return (int)_packedValue;
		}
		
		uint Color::PackedValue()
		{
			return _packedValue;
		}
		
		uint Color::InitializeFromVector4(Vector4 value) 
        { 
            byte r = (byte)(Math::Round(value.X * 255)); 
            byte g = (byte)(Math::Round(value.Y * 255)); 
            byte b = (byte)(Math::Round(value.Z * 255)); 
            byte a = (byte)(Math::Round(value.W * 255)); 
            return ((uint)a << 24) + ((uint)r << 16) + ((uint)g << 8) + b; 
        } 
  
        uint Color::InitializeFromVector3(Vector3 value) 
        { 
            byte r = (byte)(Math::Round(value.X * 255)); 
            byte g = (byte)(Math::Round(value.Y * 255)); 
            byte b = (byte)(Math::Round(value.Z * 255)); 
            return ((uint)255 << 24) + ((uint)r << 16) + ((uint)g << 8) + b; 
        } 
		
		Vector4 Color::ToVector4() 
        { 
            return Vector4((float)R() / 255, (float)G() / 255, (float)B() / 255, (float)A() / 255); 
        } 
  
        Vector3 Color::ToVector3() 
        { 
            return Vector3((float)R() / 255, (float)G() / 255, (float)B() / 255); 
        } 
		
		bool Color::operator!=(const Color other)
		{
			return !Equals(other);
		}
		
		bool Color::operator==(const Color other) 
        { 
            return Equals(other);
        }
	}
}
