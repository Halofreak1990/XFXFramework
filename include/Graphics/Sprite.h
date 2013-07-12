/*****************************************************************************
 *	Sprite.h																 *
 *																			 *
 *	XFX::Graphics::Sprite class definition file 							 *
 *	Copyright (c) XFX Team. All Rights Reserved 							 *
 *****************************************************************************/
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
		/**
		 * Internal helper class to aid drawing via the SpriteBatch.
		 */
		class Sprite : public Object
		{
		private:
			Texture2D* texture;
			Rectangle destinationRectangle;
			Rectangle sourceRectangle;
			Color color;
			float rotation;
			Vector2 origin;
			SpriteEffects_t effects;
			float layerDepth;

		public:
			Texture2D* getTexture() const;
			Rectangle DestinationRectangle() const;
			Rectangle SourceRectangle() const;
			Color getColor() const;
			float Rotation() const;
			Vector2 Origin() const;
			SpriteEffects_t Effects() const;
			float LayerDepth() const;

			Sprite();
			Sprite(Texture2D* texture, const Rectangle sourceRectangle, const Rectangle destinationRectangle, const Color color, const float rotation, const Vector2 origin, const SpriteEffects_t effects, const float layerDepth);
			Sprite(const Sprite &obj);

			static const Type& GetType();

			bool operator !=(const Sprite& right) const;
			bool operator ==(const Sprite& right) const;
		};
	}
}

#endif //_XFX_GRAPHICS_SPRITE_
