/********************************************************
 *	TextureCreationParameters.h							*
 *														*
 *	XFX TextureCreationParameters definition file		*
 *	Copyright © XFX Team. All Rights Reserved			*
 ********************************************************/
#ifndef _XFX_GRAPHICS_TEXTURECREATIONPARAMETERS_
#define _XFX_GRAPHICS_TEXTURECREATIONPARAMETERS_

#include "Color.h"
#include "Enums.h"

using namespace System;

namespace XFX
{
	namespace Graphics
	{
		// Describes the parameters to use when initializing a new instance of a texture.
		struct TextureCreationParameters : virtual Object
		{
			int Width;
			int Height;
			int Depth;
			int MipLevels;
			SurfaceFormat_t Format;
			Color ColorKey;
			FilterOptions_t Filter;
			FilterOptions_t MipFilter;
			TextureUsage_t TextureUsage_;
			static TextureCreationParameters Default;

			TextureCreationParameters(int width, int height, int depth, int mipLevels, SurfaceFormat_t format, TextureUsage_t textureUsage, Color colorKey, FilterOptions_t filter, FilterOptions_t mipFilter);
			TextureCreationParameters(const TextureCreationParameters &obj);
			TextureCreationParameters();

			bool Equals(const TextureCreationParameters other);
			int GetHashCode();
			char* ToString();
			
			bool operator!=(const TextureCreationParameters other);
			bool operator==(const TextureCreationParameters other);
		};
	}
}

#endif //_XFX_GRAPHICS_TEXTURECREATIONPARAMETERS_
