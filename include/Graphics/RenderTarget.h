/********************************************************
 *	RenderTarget.h										*
 *														*
 *	XFX RenderTarget definition file					*
 *	Copyright © XFX Team. All Rights Reserved			*
 ********************************************************/
#ifndef _XFX_GRAPHICS_RENDERTARGET_
#define _XFX_GRAPHICS_RENDERTARGET_

#include <System/Delegates.h>
#include <System/Interfaces.h>
#include "Enums.h"

using namespace System;

namespace XFX
{
	namespace Graphics
	{
		class GraphicsDevice;

		class RenderTarget : public IDisposable, virtual Object
		{
		private:
			bool isContentLost;
			bool isDisposed;

		protected:
			GraphicsDevice* graphicsDevice;
			SurfaceFormat_t format;
			int width;
			int height;
			int multiSampleQuality;
			MultiSampleType_t multiSampleType;
			RenderTargetUsage_t renderTargetUsage;
			int numLevels;

			virtual void Dispose(bool disposing);
			virtual void raise_ContentLost(Object* sender, EventArgs e);
			void raise_Disposing(Object* sender, EventArgs e);

		public:
			SurfaceFormat_t getFormat();
			GraphicsDevice* getGraphicsDevice();
			int Height();
			bool IsContentLost();
			bool IsDisposed();
			int MultiSampleQuality();
			MultiSampleType_t getMultiSampleType();
			char* Name;
			Object* Tag;
			int Width();

			EventHandler ContentLost;
			EventHandler Disposing;

			virtual ~RenderTarget();

			void Dispose();
		};
	}
}

#endif //_XFX_GRAPHICS_RENDERTARGET_
