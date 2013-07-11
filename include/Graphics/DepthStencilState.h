/*****************************************************************************
 *	DepthStencilState.h														 *
 *																			 *
 *	XFX::Graphics::DepthStencilState definition file						 *
 *	Copyright (c) XFX Team. All Rights Reserved 							 *
 *****************************************************************************/
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
			StencilOperation_t counterClockwiseStencilDepthBufferFail;
			StencilOperation_t counterClockwiseStencilFail;
			CompareFunction_t counterClockwiseStencilFunction;
			bool isBound;

		protected:
			void Dispose(bool disposing);

		public:
			static const DepthStencilState Default;
			static const DepthStencilState DepthRead;
			static const DepthStencilState None;

			StencilOperation_t getCounterClockwiseStencilDepthBufferFail() const;
			void setCounterClockwiseStencilDepthBufferFail(StencilOperation_t value);
			StencilOperation_t getCounterClockwiseStencilFail() const;
			void setCounterClockwiseStencilFail(StencilOperation_t value);
			CompareFunction_t getCounterClockwiseStencilFunction() const;
			void setCounterClockwiseStencilFunction(CompareFunction_t value);

			DepthStencilState();
			~DepthStencilState();

			static int GetType();

			bool operator==(const DepthStencilState& right) const;
			bool operator!=(const DepthStencilState& right) const;
		};
	}
}

#endif //_XFX_GRAPHICS_DEPTHSTENCILSTATE_
