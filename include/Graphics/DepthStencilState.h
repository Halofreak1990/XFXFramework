#ifndef _XFX_GRAPHICS_DEPTHSTENCILSTATE_
#define _XFX_GRAPHICS_DEPTHSTENCILSTATE_

#include "GraphicsResource.h"

namespace XFX
{
	namespace Graphics
	{
		// Contains depth-stencil state for the device.
		class DepthStencilState : public GraphicsResource
		{
		private:
			bool isBound;

		protected:
			void Dispose(bool disposing);

		public:
			static const DepthStencilState Default;
			static const DepthStencilState DepthRead;
			static const DepthStencilState None;

			DepthStencilState();
			~DepthStencilState();

			int GetType() const;

			bool operator==(const DepthStencilState& right) const;
			bool operator!=(const DepthStencilState& right) const;
		};
	}
}

#endif //_XFX_GRAPHICS_DEPTHSTENCILSTATE_
