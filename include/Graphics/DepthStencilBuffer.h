#ifndef _DEPTHSTENCILBUFFER_
#define _DEPTHSTENCILBUFFER_

#include "../System.h"
#include "Enums.h"

using namespace System;

namespace XFX
{
	namespace Graphics
	{	
		class GraphicsDevice;
		
		/// <summary>
		/// Queries and prepares depth stencil buffers.
		/// </summary>
		class DepthStencilBuffer : public IDisposable
		{
		private:
			GraphicsDevice *_graphicsDevice;
			int _width;
			int _height;
			DepthFormat_t _format;
			bool isDisposed;
			int _multiSampleQuality;
			MultiSampleType_t _multiSampleType;
			
		protected:
			virtual void Dispose(bool __p1);
			
		public:
			DepthFormat_t Format();
			GraphicsDevice *GraphicsDevice_();
			bool IsDisposed();
			int MultiSampleQuality();
			MultiSampleType_t MultiSampleType_();
			int Height();
			int Width();
			
			DepthStencilBuffer(GraphicsDevice *graphicsDevice, int width, int height, DepthFormat_t format);
			DepthStencilBuffer(GraphicsDevice *graphicsDevice, int width, int height, DepthFormat_t format, MultiSampleType_t multiSampleType, int multiSampleQuality);
			DepthStencilBuffer();
			DepthStencilBuffer(const DepthStencilBuffer &obj);
			virtual ~DepthStencilBuffer();
			
			void Dispose();
		};
	}
}

#endif //_DEPTHSTENCILBUFFER_
