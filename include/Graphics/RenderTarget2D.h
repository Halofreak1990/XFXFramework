/*****************************************************************************
 *	RenderTarget2D.h														 *
 *																			 *
 *	XFX::Graphics::RenderTarget2D definition file							 *
 *	Copyright (c) XFX Team. All Rights Reserved 							 *
 *****************************************************************************/
#ifndef _XFX_GRAPHICS_RENDERTARGET2D_
#define _XFX_GRAPHICS_RENDERTARGET2D_

#include <System/Event.h>
#include <Graphics/Texture2D.h>

using namespace System;

namespace XFX
{
	namespace Graphics
	{
		class GraphicsDevice;

		// Contains a 2D texture that can be used as a render target.
		class RenderTarget2D : public Texture2D
		{
		private:
			friend class GraphicsDevice;

			int renderBufferIdentifier;
			static int bufferCount;

			DepthFormat_t depthStencilFormat;

		protected:
			void Dispose(bool disposing);
			virtual void raise_ContentLost(Object * const sender, EventArgs * const e);

		public:
			DepthFormat_t getDepthStencilFormat() const;
			bool IsContentLost() const;
			int getMultiSampleCount() const;
			RenderTargetUsage_t getRenderTargetUsage() const;

			RenderTarget2D(GraphicsDevice * const graphicsDevice, const int width, const int height);
			RenderTarget2D(GraphicsDevice * const graphicsDevice, const int width, const int height, const bool mipmap, const SurfaceFormat_t preferredFormat, const DepthFormat_t preferredDepthFormat);
			RenderTarget2D(GraphicsDevice * const graphicsDevice, const int width, const int height, const bool mipmap, const SurfaceFormat_t preferredFormat, const DepthFormat_t preferredDepthFormat, const int multisampleCount, const RenderTargetUsage_t usage);
			~RenderTarget2D();

			EventHandler ContentLost;
			
			static int GetType();

			bool operator ==(const RenderTarget2D& right) const;
			bool operator !=(const RenderTarget2D& right) const;
		};
	}
}

#endif //_XFX_GRAPHICS_RENDERTARGET2D_
