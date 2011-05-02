/********************************************************
 *	SpriteBatch.h										*
 *														*
 *	XFX SpriteBatch definition file						*
 *	Copyright © XFX Team. All Rights Reserved			*
 ********************************************************/
#ifndef _XFX_GRAPHICS_SPRITEBATCH_
#define _XFX_GRAPHICS_SPRITEBATCH_

#include "Enums.h"
#include "GraphicsDevice.h"
#include <Matrix.h>
#include "Sprite.h"
#include "StateBlock.h"
#include <System/Collections/Generic/List.h>
#include <System/Types.h>
#include <Vector2.h>
#include <Vector4.h>

using namespace System;
using namespace System::Collections::Generic;

namespace XFX
{
	struct Rectangle;
	
	namespace Graphics
	{
		struct Color;
		class SpriteFont;
		class Texture2D;
		
		/// <summary>
		/// Enables a group of sprites to be drawn using the same settings.
		/// </summary>
		class SpriteBatch : public IDisposable, virtual Object
		{
		private:
			Texture2D* currentTexture;
			GraphicsDevice* device;
			bool isDisposed;
			bool inBeginEndPair;
			SaveStateMode_t saveStateMode;
			StateBlock saveState;
			SpriteSortMode_t spriteSortMode;
			static SpriteBlendMode_t spriteBlendMode;
			int spriteQueueCount;
			List<Sprite> SpriteList;

			void applyGraphicsDeviceSettings();
			void Flush();
			void restoreRenderState();
			
		protected:
			virtual void Dispose(bool disposing);
			
		public:
			GraphicsDevice* GraphicsDevice_();
			bool IsDisposed();

			EventHandler Disposing;

			virtual ~SpriteBatch();
			SpriteBatch(GraphicsDevice* graphicsDevice);
			SpriteBatch();
			
			void Begin();
			void Begin(SpriteBlendMode_t blendMode);
			void Begin(SpriteBlendMode_t blendMode, SpriteSortMode_t sortMode, SaveStateMode_t stateMode);
			void Begin(SpriteBlendMode_t blendMode, SpriteSortMode_t sortMode, SaveStateMode_t stateMode, Matrix transformMatrix);
			void Dispose();
			void Draw(Texture2D* texture, Rectangle destinationRectangle, Color color);
			void Draw(Texture2D* texture, Rectangle destinationRectangle, Rectangle sourceRectangle, Color color);
			void Draw(Texture2D* texture, Vector2 position, Color color);
			void Draw(Texture2D* texture, Vector2 position, Rectangle sourceRectangle, Color color);
			void Draw(Texture2D* texture, Vector2 position, Rectangle sourceRectangle, Color color, float rotation, Vector2 origin, float scale, SpriteEffects_t effects, float layerDepth);
			void Draw(Texture2D* texture, Vector2 position, Rectangle sourceRectangle, Color color, float rotation, Vector2 origin, Vector2 scale, SpriteEffects_t effects, float layerDepth);
			void Draw(Texture2D* texture, Rectangle destinationRectangle, Rectangle sourceRectangle, Color color, float rotation, Vector2 origin, SpriteEffects_t effects, float layerDepth);
			void DrawString(SpriteFont spriteFont, char* text, Vector2 position, Color color);
			void DrawString(SpriteFont spriteFont, char* text, Vector2 position, Color color, float rotation, Vector2 origin, Vector2 scale, SpriteEffects_t effects, float layerDepth);
			void DrawString(SpriteFont spriteFont, char* text, Vector2 position, Color color, float rotation, Vector2 origin, float scale, SpriteEffects_t effects, float layerDepth);

			void End();
		};
	}
}

#endif //_XFX_GRAPHICS_SPRITEBATCH_
