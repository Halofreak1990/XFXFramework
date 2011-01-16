#include <Graphics/DepthStencilBuffer.h>

namespace XFX
{
	namespace Graphics
	{
		DepthStencilBuffer()
		{
			_graphicsDevice = null;
			_width = 0;
			_height = 0;
			_format = DepthFormat::Unknown;
			_multiSampleType = MultiSampleType::None;
			isDisposed = false;
		}
		
		DepthStencilBuffer::DepthStencilBuffer(GraphicsDevice* graphicsDevice, int width, int height, DepthFormat_t format)
		{
			_graphicsDevice = graphiceDevice;
			_width = width;
			_height = height;
			_format = format;
			_multiSampleType = MultiSampleType::None;
			isDisposed = false;
		}
		
		DepthStencilBuffer::DepthStencilBuffer(GraphicsDevice* graphicsDevice, int width, int height, DepthFormat_t format, MultiSampleType_t multiSampleType, int multiSampleQuality)
		{
			_graphicsDevice = graphiceDevice;
			_width = width;
			_height = height;
			_format = format;
			_multiSampleType = multiSampleType;
			isDisposed = false;
		}

		DepthStencilBuffer::DepthStencilBuffer(const DepthStencilBuffer &obj)
		{
			_graphicsDevice = obj._graphicsDevice;
			_width = obj._width;
			_height = obj._height;
			_format = obj._format;
			_multiSampleType = obj._multiSampleType;
			isDisposed = obj.isDisposed;
		}

		DepthStencilBuffer::~DepthStencilBuffer()
		{
			Dispose(false);
		}
		
		DepthFormat_t DepthStencilBuffer::Format()
		{
			return _format;
		}
		
		GraphicsDevice* DepthStencilBuffer::GraphicsDevice_()
		{
			return _graphicsDevice;
		}
		
		bool DepthStencilBuffer::IsDisposed()
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
		
		void DepthStencilBuffer::Dispose(bool __p1)
		{
			if(__p1)
			{
			}
			
			isDisposed = true;
		}
	}
}
