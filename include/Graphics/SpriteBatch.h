/********************************************************
 *	SpriteBatch.h										*
 *														*
 *	XFX SpriteBatch definition file						*
 *	Copyright © XFX Team. All Rights Reserved			*
 ********************************************************/
#ifndef _XFX_GRAPHICS_SPRITEBATCH_
#define _XFX_GRAPHICS_SPRITEBATCH_

#include "Enums.h"
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
		class GraphicsDevice;
		class SpriteFont;
		
		// Enables a group of sprites to be drawn using the same settings.
		class SpriteBatch : public IDisposable, virtual Object
		{
		private:
			GraphicsDevice* device;
			bool isDisposed;
			bool inBeginEndPair;
			SaveStateMode_t saveStateMode;
			StateBlock* saveState;
			SpriteSortMode_t spriteSortMode;
			SpriteBlendMode_t spriteBlendMode;
			int spriteQueueCount;
			List<Sprite> SpriteList;

			void applyGraphicsDeviceSettings();
			void Flush();
			void restoreRenderState();
			
		protected:
			virtual void Dispose(bool disposing);
			
		public:
			GraphicsDevice* getGraphicsDevice() const;
			bool IsDisposed() const;

			EventHandler Disposing;

			virtual ~SpriteBatch();
			SpriteBatch(GraphicsDevice* graphicsDevice);
			
			void Begin();
			void Begin(const SpriteBlendMode_t blendMode);
			void Begin(const SpriteBlendMode_t blendMode, const SpriteSortMode_t sortMode, const SaveStateMode_t stateMode);
			void Begin(const SpriteBlendMode_t blendMode, const SpriteSortMode_t sortMode, const SaveStateMode_t stateMode, const Matrix transformMatrix);
			void Dispose();
			void Draw(Texture2D* texture, const Rectangle destinationRectangle, Color color);
			void Draw(Texture2D* texture, const Rectangle destinationRectangle, Rectangle sourceRectangle, Color color);
			void Draw(Texture2D* texture, const Vector2 position, const Color color);
			void Draw(Texture2D* texture, const Vector2 position, const Rectangle sourceRectangle, const Color color);
			void Draw(Texture2D* texture, const Vector2 position, const Rectangle sourceRectangle, const Color color, const float rotation, const Vector2 origin, const float scale, const SpriteEffects_t effects, const float layerDepth);
			void Draw(Texture2D* texture, const Vector2 position, const Rectangle sourceRectangle, const Color color, const float rotation, const Vector2 origin, const Vector2 scale, const SpriteEffects_t effects, const float layerDepth);
			void Draw(Texture2D* texture, const Rectangle destinationRectangle, const Rectangle sourceRectangle, const Color color, const float rotation, const Vector2 origin, const SpriteEffects_t effects, const float layerDepth);
			void DrawString(SpriteFont* spriteFont, const char* text, const Vector2 position, const Color color);
			void DrawString(SpriteFont* spriteFont, const char* text, const Vector2 position, const Color color, const float rotation, const Vector2 origin, const Vector2 scale, const SpriteEffects_t effects, const float layerDepth);
			void DrawString(SpriteFont* spriteFont, const char* text, const Vector2 position, const Color color, const float rotation, const Vector2 origin, const float scale, const SpriteEffects_t effects, const float layerDepth);
			void End();
		};
	}
}

#endif //_XFX_GRAPHICS_SPRITEBATCH_
