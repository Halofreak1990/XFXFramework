#ifndef _XFX_GRAPHICS_SAMPLERSTATE_
#define _XFX_GRAPHICS_SAMPLERSTATE_

#include "GraphicsResource.h"

namespace XFX
{
	namespace Graphics
	{
		// Contains sampler state, which determines how to sample texture data.
		class SamplerState : GraphicsResource
		{
		private:
			TextureAddressMode_t addressU;
			TextureAddressMode_t addressV;
			TextureAddressMode_t addressW;
			TextureFilter_t filter;
			bool isBound;
			int maxAnisotropy;
			int maxMipLevel;
			int mipMapLevelOfDetailBias;

		protected:
			void Dispose(bool disposing);

		public:
			TextureAddressMode_t getAddressU() const;
			void setAddressU(TextureAddressMode_t value);
			TextureAddressMode_t getAddressV() const;
			void setAddressV(TextureAddressMode_t value);
			TextureAddressMode_t getAddressW() const;
			void setAddressW(TextureAddressMode_t value);
			TextureFilter_t getFilter() const;
			void setFilter(TextureFilter_t value);
			int getMaxAnisotropy() const;
			void setMaxAnisotropy(int value);
			int getMaxMipLevel() const;
			void setMaxMipLevel(int value);
			int getMipMapLevelOfDetailBias() const;
			void setMipMapLevelOfDetailBias(int value);

			static const SamplerState AnisotropicClamp;
			static const SamplerState AnisotropicWrap;
			static const SamplerState LinearClamp;
			static const SamplerState LinearWrap;
			static const SamplerState PointClamp;
			static const SamplerState PointWrap;

			SamplerState();
			~SamplerState();

			int GetType() const;

			bool operator==(const SamplerState& right) const;
			bool operator!=(const SamplerState& right) const;
		};
	}
}

#endif //_XFX_GRAPHICS_SAMPLERSTATE_
