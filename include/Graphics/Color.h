/*****************************************************************************
 *	Color.h 																 *
 *																			 *
 *	XFX::Graphics::Color structure definition file  						 *
 *	Copyright (c) XFX Team. All Rights Reserved 							 *
 *****************************************************************************/
#ifndef _XFX_GRAPHICS_COLOR_
#define _XFX_GRAPHICS_COLOR_

#include <System/Interfaces.h>

using namespace System;

namespace XFX
{
	struct Vector3;
	struct Vector4;
	
	namespace Graphics
	{
		/**
		 * Represents a color using Red, Green, Blue, and Alpha values.
		 */
		struct Color : IEquatable<Color>, Object
		{
		private:
			uint _packedValue;

			unsigned int RGBAtoARGB(uint value);
			Color(unsigned int packedValue);
			static unsigned int InitializeFromVector4(const Vector4 vector);
			static unsigned int InitializeFromVector3(const Vector3 vector);
		
		public:
			byte A() const;
			static const Color AliceBlue;
			static const Color AntiqueWhite;
			static const Color Aqua;
			static const Color AquaMarine;
			static const Color Azure;
			byte B() const;
			static const Color Beige;
			static const Color Bisque;
			static const Color Black;
			static const Color BlanchedAlmond;
			static const Color Blue;
			static const Color BlueViolet;
			static const Color Brown;
			static const Color BurlyWood;
			static const Color CadetBlue;
			static const Color Chartreuse;
			static const Color Chocolate;
			static const Color Coral;
			static const Color CornflowerBlue;
			static const Color Cornsilk;
			static const Color Crimson;
			static const Color Cyan;
			static const Color DarkBlue;
			static const Color DarkCyan;
			static const Color DarkGoldenrod;
			static const Color DarkGray;
			static const Color DarkGreen;
			static const Color DarkKhaki;
			static const Color DarkMagenta;
			static const Color DarkOliveGreen;
			static const Color DarkOrange;
			static const Color DarkOrchid;
			static const Color DarkRed;
			static const Color DarkSalmon;
			static const Color DarkSeaGreen;
			static const Color DarkSlateBlue;
			static const Color DarkSlateGray;
			static const Color DarkTurquoise;
			static const Color DarkViolet;
			static const Color DeepPink;
			static const Color DeepSkyBlue;
			static const Color DimGray;
			static const Color DodgerBlue;
			static const Color FireBrick;
			static const Color FloralWhite;
			static const Color ForestGreen;
			static const Color Fuchsia;
			byte G() const;
			static const Color Gainsboro;
			static const Color GhostWhite;
			static const Color Gold;
			static const Color Goldenrod;
			static const Color Gray;
			static const Color Green;
			static const Color GreenYellow;
			static const Color Honeydew;
			static const Color HotPink;
			static const Color IndianRed;
			static const Color Indigo;
			static const Color Ivory;
			static const Color Khaki;
			static const Color Lavender;
			static const Color LavenderBlush;
			static const Color LawnGreen;
			static const Color LemonChiffon;
			static const Color LightBlue;
			static const Color LightCoral;
			static const Color LightCyan;
			static const Color LightGoldenrodYellow;
			static const Color LightGray;
			static const Color LightGreen;
			static const Color LightPink;
			static const Color LightSalmon;
			static const Color LightSeaGreen;
			static const Color LightSkyBlue;
			static const Color LightSlateGray;
			static const Color LightSteelBlue;
			static const Color LightYellow;
			static const Color Lime;
			static const Color LimeGreen;
			static const Color Linen;
			static const Color Magenta;
			static const Color Maroon;
			static const Color MediumAquamarine;
			static const Color MediumBlue;
			static const Color MediumOrchid;
			static const Color MediumPurple;
			static const Color MediumSeaGreen;
			static const Color MediumSlateBlue;
			static const Color MediumSpringGreen;
			static const Color MediumTurquoise;
			static const Color MediumVioletRed;
			static const Color MidnightBlue;
			static const Color MintCream;
			static const Color MistyRose;
			static const Color Moccasin;
			static const Color NavajoWhite;
			static const Color Navy;
			static const Color OldLace;
			static const Color Olive;
			static const Color OliveDrab;
			static const Color Orange;
			static const Color OrangeRed;
			static const Color Orchid;
			static const Color PaleGoldenrod;
			static const Color PaleGreen;
			static const Color PaleTurquoise;
			static const Color PaleVioletRed;
			static const Color PapayaWhip;
			static const Color PeachPuff;
			static const Color Peru;
			static const Color Pink;
			static const Color Plum;
			static const Color PowderBlue;
			static const Color Purple;
			byte R() const;
			static const Color Red;
			static const Color RosyBrown;
			static const Color RoyalBlue;
			static const Color SaddleBrown;
			static const Color Salmon;
			static const Color SandyBrown;
			static const Color SeaGreen;
			static const Color SeaShell;
			static const Color Sienna;
			static const Color Silver;
			static const Color SkyBlue;
			static const Color SlateBlue;
			static const Color SlateGray;
			static const Color Snow;
			static const Color SpringGreen;
			static const Color SteelBlue;
			static const Color Tan;
			static const Color Teal;
			static const Color Thistle;
			static const Color Tomato;
			static const Color TransparentBlack;
			static const Color TransparentWhite;
			static const Color Turquoise;
			static const Color Violet;
			static const Color Wheat;
			static const Color White;
			static const Color WhiteSmoke;
			static const Color Yellow;
			static const Color YellowGreen;
			
			Color();
			Color(const Vector3 vector);
			Color(const Vector4 vector);
			Color(const byte r, const byte g, const byte b);
			Color(const byte r, const byte g, const byte b, const byte a);
			Color(const Color &obj);
			
			bool Equals(Object const * const obj) const;
			bool Equals(const Color other) const;
			int GetHashCode() const;
			static const Type& GetType();
			unsigned int PackedValue() const;
			const String ToString() const;
			Vector4 ToVector4() const;
			Vector3 ToVector3() const;
			
			bool operator!=(const Color& other) const;
			bool operator==(const Color& other) const;
			Color operator *(const float scale) const;
		};
	}
}

#endif //_COLOR_
