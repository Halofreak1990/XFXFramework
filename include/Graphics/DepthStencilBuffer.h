#ifndef _XFX_GRAPHICS_DEPTHSTENCILBUFFER_
#define _XFX_GRAPHICS_DEPTHSTENCILBUFFER_

#include <System/Interfaces.h>
#include <System/Types.h>
#include "Enums.h"

using namespace System;

namespace XFX
{
	namespace Graphics
	{	
		class GraphicsDevice;
		
		// Queries and prepares depth stencil buffers.
		class DepthStencilBuffer : public IDisposable, virtual Object
		{
		private:
			GraphicsDevice* _graphicsDevice;
			DepthFormat_t _format;
			bool isDisposed;
			int _multiSampleQuality;
			MultiSampleType_t _multiSampleType;
			
		protected:
			virtual void Dispose(bool __p1);
			
		public:
			DepthFormat_t Format();
			GraphicsDevice* getGraphicsDevice();
			bool IsDisposed();
			int MultiSampleQuality();
			MultiSampleType_t getMultiSampleType();
			const int Height;
			const int Width;
			
			DepthStencilBuffer(GraphicsDevice* graphicsDevice, const int width, const int height, DepthFormat_t format);
			DepthStencilBuffer(GraphicsDevice* graphicsDevice, const int width, const int height, DepthFormat_t format, MultiSampleType_t multiSampleType, int multiSampleQuality);
			DepthStencilBuffer(const DepthStencilBuffer &obj);
			virtual ~DepthStencilBuffer();
			
			void Dispose();
		};
	}
}

#endif //_XFX_GRAPHICS_DEPTHSTENCILBUFFER_
