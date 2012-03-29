/********************************************************
 *	TextureInformation.h								*
 *														*
 *	XFX TextureInformation definition file				*
 *	Copyright © XFX Team. All Rights Reserved			*
 ********************************************************/
#ifndef _XFX_GRAPHICS_TEXTUREINFORMATION_
#define _XFX_GRAPHICS_TEXTUREINFORMATION_

#include "Enums.h"
#include <System/Object.h>

using namespace System;

namespace XFX
{
	namespace Graphics
	{
		//	Encapsulates information describing texture resources.
		struct TextureInformation : virtual Object
		{
			int Depth;
			SurfaceFormat_t Format;
			int Height;
			ImageFileFormat_t ImageFormat;
			int MipLevels;
			ResourceType_t ResourceType_;
			int Width;

			TextureInformation(int width, int height, int depth, int mipLevels, SurfaceFormat_t format);
			TextureInformation(const TextureInformation &obj); //Copy Constructor
			TextureInformation(); // Default Constructor

			bool Equals(TextureInformation other);
			int GetHashCode();
			char* ToString();

			bool operator!=(const TextureInformation other);
			bool operator==(const TextureInformation other);
		};
	}
}

#endif //_XFX_GRAPHICS_TEXTUREINFORMATION_
