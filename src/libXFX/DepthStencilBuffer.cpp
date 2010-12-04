#include <Graphics/DepthStencilBuffer.h>

namespace XFX
{
	namespace Graphics
	{
		DepthStencilBuffer()
		{
			_width = 0;
			_height = 0;
			_format = DepthFormat::Unknown;
			_multiSampleType = MultiSampleType::None;
			isDisposed = false;
		}
		
		DepthStencilBuffer::DepthStencilBuffer(GraphicsDevice &graphicsDevice, int width, int height, DepthFormat_t format)
		{
			_width = width;
			_height = height;
			_format = format;
			_multiSampleType = MultiSampleType::None;
			isDisposed = false;
		}
		
		DepthStencilBuffer(GraphicsDevice &graphicsDevice, int width, int height, DepthFormat_t format, MultiSampleType_t multiSampleType, int multiSampleQuality)
		{
			_width = width;
			_height = height;
			_format = format;
			_multiSampleType = multiSampleType;
			isDisposed = false;
		}
		
		DepthFormat_t DepthStencilBuffer::Format()
		{
			return _format;
		}
		
		GraphicsDevice DepthStencilBuffer::GraphicsDevice_()
		{
			return _graphicsDevice;
		}
		
		int DepthStencilBuffer::IsDisposed()
		{
			return isDisposed();
		}
		
		int DepthStencilBuffer::Height()
		{
			return _height;
		}
		
		int DepthStencilBuffer::Width()
		{
			return _width;
		}
		
		void DepthStencilBuffer::Dispose()
		{
			Dispose(true);
		}
		
		void DepthStencilBuffer::Dispose(int __p1)
		{
			if(__p1)
			{
			}
			
			isDisposed = true;
		}
	}
}
