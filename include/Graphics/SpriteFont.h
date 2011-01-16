/********************************************************
 *	SpriteFont.h										*
 *														*
 *	XFX SpriteFont definition file						*
 *	Copyright © XFX Team. All Rights Reserved			*
 ********************************************************/
#ifndef _XFX_GRAPHICS_SPRITEFONT_
#define _XFX_GRAPHICS_SPRITEFONT_

#include <Rectangle.h>
#include "Texture2D.h"
#include <Vector3.h>
#include <System/Collections/Generic/List.h>
#include <System/Types.h>

using namespace System;
using namespace System::Collections::Generic;

namespace XFX
{
	struct Vector2;

	namespace Graphics
	{
		class SpriteBatch;

		/// <summary>
		/// Represents a font texture.
		/// </summary>
		class SpriteFont
		{
		private:
			List<char> characterMap;
			List<Rectangle> croppingData;
			List<Rectangle> glyphData;
			List<Vector3> kerning;
			int lineSpacing;
			float spacing;
			Texture2D textureValue;

			int GetIndexForCharacter(char character);

		public:
			int LineSpacing();
			float Spacing;

			SpriteFont(Texture2D texture, List<Rectangle> glyphs, List<Rectangle> cropping, List<char> charMap, int lineSpacing, float spacing, List<Vector3> kerning);

			void Draw(char* text, SpriteBatch spriteBatch, Vector2 textblockPosition, Color color, float rotation, Vector2 origin, Vector2 scale, SpriteEffects_t spriteEffects, float depth);
			Vector2 MeasureString(char* text);
		};
	}
}

#endif //_XFX_GRAPHICS_SPRITEFONT_
