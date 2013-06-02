/********************************************************
 *	SpriteFont.h										*
 *														*
 *	XFX SpriteFont definition file						*
 *	Copyright (c) XFX Team. All Rights Reserved			*
 ********************************************************/
#ifndef _XFX_GRAPHICS_SPRITEFONT_
#define _XFX_GRAPHICS_SPRITEFONT_

#include <Rectangle.h>
#include "Texture2D.h"
#include <Vector3.h>
#include <System/Collections/Generic/List.h>
#include <System/Object.h>
#include <System/Types.h>

using namespace System;
using namespace System::Collections::Generic;

namespace XFX
{
	struct Vector2;

	namespace Graphics
	{
		class SpriteBatch;

		// Represents a font texture.
		class SpriteFont : public virtual Object
		{
		private:
			friend class SpriteBatch;

			List<char> characterMap;
			List<Rectangle> croppingData;
			List<Rectangle> glyphData;
			List<Vector3> kerning;
			int lineSpacing;
			float spacing;
			Texture2D* textureValue;

			int GetIndexForCharacter(char character);

			SpriteFont(Texture2D * const texture, const List<Rectangle>& glyphs, const List<Rectangle>& cropping, const List<char>& charMap, const int lineSpacing, const float spacing, const List<Vector3>& kerning);

			void Draw(String& text, SpriteBatch * const spriteBatch, const Vector2 textblockPosition, const Color color, const float rotation, const Vector2 origin, const Vector2 scale, const SpriteEffects_t spriteEffects, const float depth);

		public:
			int LineSpacing();
			float Spacing;

			virtual ~SpriteFont();

			Vector2 MeasureString(String& text) const;
		};
	}
}

#endif //_XFX_GRAPHICS_SPRITEFONT_
