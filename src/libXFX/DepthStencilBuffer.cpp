#include <Graphics/DepthStencilBuffer.h>
#include <Graphics/GraphicsDevice.h>

namespace XFX
{
	namespace Graphics
	{
		DepthStencilBuffer::DepthStencilBuffer(GraphicsDevice* graphicsDevice, const int width, const int height, DepthFormat_t format)
			: Height(height), Width(width)
		{
			_graphicsDevice = graphicsDevice;
			_format = format;
			_multiSampleType = MultiSampleType::None;
			isDisposed = false;
		}
		
		DepthStencilBuffer::DepthStencilBuffer(GraphicsDevice* graphicsDevice, const int width, const int height, DepthFormat_t format, MultiSampleType_t multiSampleType, int multiSampleQuality)
			: Height(height), Width(width)
		{
			_graphicsDevice = graphicsDevice;
			_format = format;
			_multiSampleType = multiSampleType;
			isDisposed = false;
		}

		DepthStencilBuffer::DepthStencilBuffer(const DepthStencilBuffer &obj)
			: Height(height), Width(width)
		{
			_graphicsDevice = obj._graphicsDevice;
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
		
		GraphicsDevice* DepthStencilBuffer::getGraphicsDevice()
		{
			return _graphicsDevice;
		}
		
		bool DepthStencilBuffer::IsDisposed()
		{
			return isDisposed;
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
