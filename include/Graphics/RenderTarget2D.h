/********************************************************
 *	RenderTarget2D.h									*
 *														*
 *	XFX RenderTarget2D definition file					*
 *	Copyright © XFX Team. All Rights Reserved			*
 ********************************************************/
#ifndef _XFX_GRAPHICS_RENDERTARGET2D_
#define _XFX_GRAPHICS_RENDERTARGET2D_

#include <System/Types.h>
#include "RenderTarget.h"
//#include "Texture2D.h"

using namespace System;

namespace XFX
{
	namespace Graphics
	{
		class GraphicsDevice;
		class Texture2D;

		class RenderTarget2D : public RenderTarget, virtual Object
		{
		private:
			Texture2D* texture;
			int renderBufferIdentifier;

		protected:
			void Dispose(bool disposing);

		public:
			RenderTarget2D(GraphicsDevice* graphicsDevice, int width, int height, int numberLevels, SurfaceFormat_t format);
			RenderTarget2D(GraphicsDevice* graphicsDevice, int width, int height, int numberLevels, SurfaceFormat_t format, MultiSampleType_t multiSampleType, int multiSampleQuality);
			RenderTarget2D(GraphicsDevice* graphicsDevice, int width, int height, int numberLevels, SurfaceFormat_t format, RenderTargetUsage_t usage);
			RenderTarget2D(GraphicsDevice* graphicsDevice, int width, int height, int numberLevels, SurfaceFormat_t format, MultiSampleType_t multiSampleType, int multiSampleQuality, RenderTargetUsage_t usage);

			Texture2D* GetTexture();
		};
	}
}

#endif //_XFX_GRAPHICS_RENDERTARGET2D_
