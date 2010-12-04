/********************************************************
 *	SpriteBatch.h										*
 *														*
 *	XFX SpriteBatch definition file						*
 *	Copyright © XFX Team. All Rights Reserved			*
 ********************************************************/
#ifndef _SPRITEBATCH_
#define _SPRITEBATCH_

#include "../System.h"
#include "Enums.h"

using namespace System;

namespace XFX
{
	class Matrix;
	class Rectangle;
	class Vector2;
	
	namespace Graphics
	{
		class Color;
		class Sprite;
		class SpriteFont;
		class Texture2D;
		
		class SpriteBatch : IDisposable
		{
			private:
				GraphicsDevice *device;
				int disposed;
				static SpriteBlendMode_t spriteBlendMode;
				
				void applyGraphicsDeviceSettings();
				void flush();
				void restoreRenderState();
				
			protected:
				virtual void Dispose(int disposing);
				
			public:
				~SpriteBatch();
				SpriteBatch(GraphicsDevice &graphicsDevice);
				
				void Begin();
				void Begin(SpriteBlendMode_t blendMode, SpriteSortMode_t sortMode, SaveStateMode_t stateMode);
				void Begin(SpriteBlendMode_t blendMode, SpriteSortMode_t sortMode, SaveStateMode_t stateMode, Matrix &transformMatrix);
				void Dispose();
				void Draw(Texture2D &texture, Rectangle &destinationRectangle, Color &color);
				void Draw(Texture2D &texture, Rectangle &destinationRectangle, Rectangle &sourceRectangle, Color &color);
				void Draw(Texture2D &texture, Vector2 &position, Color &color);
				void Draw(Texture2D &texture, Vector2 &position, Rectangle &sourceRectangle, Color &color);
				void Draw(Texture2D &texture, Vector2 &position, Rectangle &sourceRectangle, Color &color, float rotation, Vector2 origin, float scale, SpriteEffects_t effects, float layerDepth);
				void Draw(Texture2D &texture, Vector2 &position, Rectangle &sourceRectangle, Color &color, float rotation, Vector2 &origin, Vector2 &scale, SpriteEffects_t effects, float layerDepth);
				void Draw(Texture2D &texture, Rectangle &destinationRectangle, Rectangle &sourceRectangle, Color &color, float rotation, Vector2 &origin, SpriteEffects_t &effects, float layerDepth);
				void DrawString(SpriteFont &spriteFont, char* text, Vector2 &position, Color &color);
				void DrawString(SpriteFont &spriteFont, char* text, Vector2 &position, Color &color, float rotation, Vector2 &origin, float scale, SpriteEffects_t effects, float layerDepth);
				
				void End();
		};
	}
}

#endif //_SPRITEBATCH_
