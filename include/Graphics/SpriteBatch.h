/*****************************************************************************
 *	SpriteBatch.h															 *
 *																			 *
 *	XFX::Graphics::SpriteBatch class definition file						 *
 *	Copyright (c) XFX Team. All Rights Reserved 							 *
 *****************************************************************************/
#ifndef _XFX_GRAPHICS_SPRITEBATCH_
#define _XFX_GRAPHICS_SPRITEBATCH_

#include "BlendState.h"
#include "DepthStencilState.h"
#include "Effect.h"
#include "Enums.h"
#include "GraphicsResource.h"
#include <Matrix.h>
#include "RasterizerState.h"
#include "SamplerState.h"
#include "Sprite.h"
#include "StateBlock.h"
#include <System/Collections/Generic/List.h>
#include <System/Nullable.h>
#include <System/String.h>
#include <System/Types.h>

using namespace System;
using namespace System::Collections::Generic;

namespace XFX
{
	struct Rectangle;
	struct Vector2;
	
	namespace Graphics
	{
		struct Color;
		class GraphicsDevice;
		class SpriteFont;
		
		/**
		 * Enables a group of sprites to be drawn using the same settings.
		 */
		class SpriteBatch : public GraphicsResource, public Object
		{
		private:
			bool inBeginEndPair;
			//SaveStateMode_t saveStateMode;
			StateBlock* saveState;
			SpriteSortMode_t spriteSortMode;
			//SpriteBlendMode_t spriteBlendMode;
			int spriteQueueCount;
			BlendState oldBlendState;
			BlendState blendState;
			List<Sprite> SpriteList;

			void applyGraphicsDeviceSettings();
			void Flush();
			void restoreRenderState();
			
		protected:
			void Dispose(bool disposing);
			
		public:
			SpriteBatch(GraphicsDevice * const graphicsDevice);
			virtual ~SpriteBatch();
			
			void Begin();
			void Begin(SpriteSortMode_t sortMode, const BlendState& blendState);
			void Begin(SpriteSortMode_t sortMode, const BlendState& blendState, const SamplerState& samplerState, const DepthStencilState& depthStencilState, const RasterizerState& rasterizerState);
			void Begin(SpriteSortMode_t sortMode, const BlendState& blendState, const SamplerState& samplerState, const DepthStencilState& depthStencilState, const RasterizerState& rasterizerState, Effect * const effect);
			void Begin(SpriteSortMode_t sortMode, const BlendState& blendState, const SamplerState& samplerState, const DepthStencilState& depthStencilState, const RasterizerState& rasterizerState, Effect * const effect, const Matrix transformMatrix);
			void Draw(Texture2D * const texture, const Rectangle destinationRectangle, Color color);
			void Draw(Texture2D * const texture, const Rectangle destinationRectangle, const Nullable<Rectangle> sourceRectangle, Color color);
			void Draw(Texture2D * const texture, const Vector2 position, const Color color);
			void Draw(Texture2D * const texture, const Vector2 position, const Nullable<Rectangle> sourceRectangle, const Color color);
			void Draw(Texture2D * const texture, const Vector2 position, const Nullable<Rectangle> sourceRectangle, const Color color, const float rotation, const Vector2 origin, const float scale, const SpriteEffects_t effects, const float layerDepth);
			void Draw(Texture2D * const texture, const Vector2 position, const Nullable<Rectangle> sourceRectangle, const Color color, const float rotation, const Vector2 origin, const Vector2 scale, const SpriteEffects_t effects, const float layerDepth);
			void Draw(Texture2D * const texture, const Rectangle destinationRectangle, const Nullable<Rectangle> sourceRectangle, const Color color, const float rotation, const Vector2 origin, const SpriteEffects_t effects, const float layerDepth);
			void DrawString(SpriteFont * const spriteFont, String& text, const Vector2 position, const Color color);
			void DrawString(SpriteFont * const spriteFont, String& text, const Vector2 position, const Color color, const float rotation, const Vector2 origin, const Vector2 scale, const SpriteEffects_t effects, const float layerDepth);
			void DrawString(SpriteFont * const spriteFont, String& text, const Vector2 position, const Color color, const float rotation, const Vector2 origin, const float scale, const SpriteEffects_t effects, const float layerDepth);
			void End();
			static const Type& GetType();
		};
	}
}

#endif //_XFX_GRAPHICS_SPRITEBATCH_
