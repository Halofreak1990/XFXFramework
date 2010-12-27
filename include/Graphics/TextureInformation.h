/********************************************************
 *	TextureInformation.h								*
 *														*
 *	XFX TextureInformation definition file				*
 *	Copyright © XFX Team. All Rights Reserved			*
 ********************************************************/
#ifndef _TEXTUREINFORMATION_
#define _TEXTUREINFORMATION_

#include "Enums.h"

namespace XFX
{
	namespace Graphics
	{
		/// <summary>
		///	Encapsulates information describing texture resources.
		/// </summary>
		struct TextureInformation
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
			TextureInformation operator=(const TextureInformation other);
		};
	}
}

#endif //_TEXTUREINFORMATION_
