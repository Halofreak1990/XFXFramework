/********************************************************
 *	Sprite.h											*
 *														*
 *	XFX Sprite definition file							*
 *	Copyright © XFX Team. All Rights Reserved			*
 ********************************************************/
#ifndef _XFX_GRAPHICS_SPRITE_
#define _XFX_GRAPHICS_SPRITE_

#include "Color.h"
#include "Enums.h"
#include "Texture2D.h"
#include <Rectangle.h>
#include <Vector2.h>

using namespace System;

namespace XFX
{
	namespace Graphics
	{
		// 
		class Sprite : virtual Object
		{
		private:
			Texture2D texture;
			Rectangle destinationRectangle;
			Rectangle sourceRectangle;
			Color color;
			float rotation;
			Vector2 origin;
			SpriteEffects_t effects;
			float layerDepth;

		public:
			Texture2D getTexture();
			Rectangle DestinationRectangle();
			Rectangle SourceRectangle();
			Color getColor();
			float Rotation();
			Vector2 Origin();
			SpriteEffects_t Effects();
			float LayerDepth();

			Sprite();
			Sprite(Texture2D texture, Rectangle sourceRectangle, Rectangle destinationRectangle, Color color, float rotation, Vector2 origin, SpriteEffects_t effects, float layerDepth);

			bool operator !=(Sprite right);
			bool operator ==(Sprite right);
		};
	}
}

#endif //_XFX_GRAPHICS_SPRITE_
