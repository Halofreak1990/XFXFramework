#ifndef _XFX_GRAPHICS_BLENDSTATE_
#define _XFX_GRAPHICS_BLENDSTATE_

#include <Graphics/Color.h>
#include <Graphics/Enums.h>
#include <Graphics/GraphicsResource.h>

namespace XFX
{
	namespace Graphics
	{
		// Contains blend state for the device.
		class BlendState : public GraphicsResource
		{
		private:
			BlendFunction_t alphaBlendFunction;
			Blend_t alphaDestinationBlend;
			Blend_t alphaSourceBlend;
			Color blendFactor;
			BlendFunction_t colorBlendFunction;
			Blend_t colorDestinationBlend;
			Blend_t colorSourceBlend;
			ColorWriteChannels_t colorWriteChannels;
			ColorWriteChannels_t colorWriteChannels1;
			ColorWriteChannels_t colorWriteChannels2;
			ColorWriteChannels_t colorWriteChannels3;
			bool isBound;
			int multiSampleMask;

		protected:
			void Dispose(bool disposing);

		public:
			static const BlendState Additive;
			static const BlendState AlphaBlend;
			static const BlendState NonPremultiplied;
			static const BlendState Opague;

			BlendFunction_t getAlphaBlendFunction() const;
			void setAlphaBlendFunction(BlendFunction_t value);
			int getMultiSampleMask() const;
			void setMultiSampleMask(int value);

			BlendState();
			~BlendState();

			int GetType() const;

			bool operator==(const BlendState& right) const;
			bool operator!=(const BlendState& right) const;
		};
	}
}

#endif //_XFX_GRAPHICS_BLENDSTATE_
