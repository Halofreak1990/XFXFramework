/*****************************************************************************
 *	RasterizerState.h														 *
 *																			 *
 *	XFX::Graphics::RasterizerState class definition file					 *
 *	Copyright (c) XFX Team. All Rights Reserved 							 *
 *****************************************************************************/
#ifndef _XFX_GRAPHICS_RASTERIZERSTATE_
#define _XFX_GRAPHICS_RASTERIZERSTATE_

#include "GraphicsResource.h"

namespace XFX
{
	namespace Graphics
	{
		/**
		 * Contains rasterizer state, which determines how to convert vector data (shapes) into raster data (pixels).
		 */
		class RasterizerState : public GraphicsResource
		{
		private:
			CullMode_t cullMode;
			float dephtBias;
			FillMode_t fillMode;
			bool isBound;
			bool multiSampleAntiAlias;
			bool scissorTestEnable;
			float slopeScaleDepthBias;

		protected:
			void Dispose(bool disposing);

		public:
			CullMode_t getCullMode() const;
			void setCullMode(CullMode_t value);
			float getDepthBias() const;
			void setDepthBias(float value);
			FillMode_t getFillMode() const;
			void setFillMode(FillMode_t value);
			bool getMultiSampleAntiAlias() const;
			void setMultiSampleAntiAlias(bool value);
			bool getScissorTestEnable() const;
			void setScissorTestEnable(bool value);
			float getSlopeScaleDepthBias() const;
			void setSlopeScaleDepthBias(float value);

			static const RasterizerState CullClockwise;
			static const RasterizerState CullCounterClockwise;
			static const RasterizerState CullNone;

			RasterizerState();

			static const Type& GetType();

			bool operator==(const RasterizerState& right) const;
			bool operator!=(const RasterizerState& right) const;
		};
	}
}

#endif //_XFX_GRAPHICS_RASTERIZERSTATE_
