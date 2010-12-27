/********************************************************
 *	SpriteBatch.h										*
 *														*
 *	XFX SpriteBatch definition file						*
 *	Copyright © XFX Team. All Rights Reserved			*
 ********************************************************/
#ifndef _SPRITEBATCH_
#define _SPRITEBATCH_

#include <System/Types.h>
#include "Enums.h"

using namespace System;

namespace XFX
{
	struct Matrix;
	struct Rectangle;
	struct Vector2;
	
	namespace Graphics
	{
		struct Color;
		class SpriteFont;
		class Texture2D;
		
		/// <summary>
		/// Enables a group of sprites to be drawn using the same settings.
		/// </summary>
		class SpriteBatch : public IDisposable
		{
		private:
			GraphicsDevice* device;
			bool disposed;
			static SpriteBlendMode_t spriteBlendMode;
			
			void applyGraphicsDeviceSettings();
			void flush();
			void restoreRenderState();
			
		protected:
			virtual void Dispose(bool disposing);
			
		public:
			GraphicsDevice GraphicsDevice_();
			bool IsDisposed();

			EventHandler Disposing;

			~SpriteBatch();
			SpriteBatch(GraphicsDevice graphicsDevice);
			
			void Begin();
			void Begin(SpriteBlendMode_t blendMode);
			void Begin(SpriteBlendMode_t blendMode, SpriteSortMode_t sortMode, SaveStateMode_t stateMode);
			void Begin(SpriteBlendMode_t blendMode, SpriteSortMode_t sortMode, SaveStateMode_t stateMode, Matrix transformMatrix);
			void Dispose();
			void Draw(Texture2D texture, Rectangle destinationRectangle, Color color);
			void Draw(Texture2D texture, Rectangle destinationRectangle, Rectangle* sourceRectangle, Color color);
			void Draw(Texture2D texture, Vector2 position, Color color);
			void Draw(Texture2D texture, Vector2 position, Rectangle* sourceRectangle, Color color);
			void Draw(Texture2D texture, Vector2 position, Rectangle* sourceRectangle, Color color, float rotation, Vector2 origin, float scale, SpriteEffects_t effects, float layerDepth);
			void Draw(Texture2D texture, Vector2 position, Rectangle* sourceRectangle, Color color, float rotation, Vector2 origin, Vector2 scale, SpriteEffects_t effects, float layerDepth);
			void Draw(Texture2D texture, Rectangle destinationRectangle, Rectangle* sourceRectangle, Color color, float rotation, Vector2 origin, SpriteEffects_t &effects, float layerDepth);
			void DrawString(SpriteFont spriteFont, char* text, Vector2 position, Color color);
			void DrawString(SpriteFont spriteFont, char* text, Vector2 position, Color color, float rotation, Vector2 origin, float scale, SpriteEffects_t effects, float layerDepth);
			
			void End();
		};
	}
}

#endif //_SPRITEBATCH_
