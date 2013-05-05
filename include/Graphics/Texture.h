/********************************************************
 *	Texture.h											*
 *														*
 *	XFX Texture definition file							*
 *	Copyright © XFX Team. All Rights Reserved			*
 ********************************************************/
#ifndef _XFX_GRAPHICS_TEXTURE_
#define _XFX_GRAPHICS_TEXTURE_

#include <System/Types.h>
#include <System/IO/Stream.h>
#include "GraphicsResource.h"

namespace XFX
{
	namespace Graphics
	{
		// Represents a texture resource.
		class Texture : public GraphicsResource
		{
		private:
			static ImageFileFormat_t ILimageformat2XNAimageformat(int ILFormat);
			int _levelCount;
			
		protected:
			virtual void Dispose(bool disposing);
		
		public:
			SurfaceFormat_t getFormat() const;
			int getLevelCount() const;
			virtual bool MustClamp() const;

			Texture();
			~Texture();
			
			void GenerateMipMaps(const TextureFilter_t filterType);
			int GetType() const;
		};
	}
}

#endif //_XFX_GRAPHICS_TEXTURE_
