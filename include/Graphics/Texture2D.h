/********************************************************
 *	Texture2D.h											*
 *														*
 *	XFX Texture2D definition file						*
 *	Copyright © XFX Team. All Rights Reserved			*
 ********************************************************/
#ifndef _XFX_GRAPHICS_TEXTURE2D_
#define _XFX_GRAPHICS_TEXTURE2D_

#include "Texture.h"
#include <System/IO/Stream.h>
#include <System/Types.h>

using namespace System; 
using namespace System::IO;

namespace XFX
{
	struct Rectangle;
	
	namespace Graphics
	{
		class GraphicsDevice;

		// 
		class Texture2D : public Texture
		{
		private:
 			bool _isDisposed; // True when the texture has been disposed 
 			int _numberOfLevels; // The number of mip levels for the texture 
 			SurfaceFormat_t _surfaceFormat; // The colour format of the texture 
 			int textureId; // The reference ID of the texture in OpenGL memory 
			uint* textureData;
 				
 			void Load(byte buffer[]);
 			
 		protected:
 			void Dispose(bool disposing);
 			
 		public:
			Rectangle getBounds() const;
 			SurfaceFormat_t Format() const;
 			const int Height;
 			const int Width;
 			
			Texture2D();
 			Texture2D(GraphicsDevice * const graphicsDevice, const int width, const int height);
			Texture2D(GraphicsDevice * const graphicsDevice, const int width, const int height, bool mipmap, const SurfaceFormat_t format);
			virtual ~Texture2D();

			static Texture2D* FromStream(GraphicsDevice * const graphicsDevice, Stream * const stream);
			static Texture2D* FromStream(GraphicsDevice * const graphicsDevice, Stream * const stream, int width, int height, bool zoom);
 			void GetData(uint data[], const int startIndex, const int elementCount) const;
			int GetType() const;
			void SaveAsJpeg(Stream * const stream, int width, int height);
			void SaveAsPng(Stream * const stream, int width, int height);
 			void SetData(uint data[], const int startIndex, const int elementCount, const SetDataOptions_t options);

			bool operator ==(const Texture2D& right) const;
			bool operator !=(const Texture2D& right) const;
		};
	}
}

#endif //_XFX_GRAPHICS_TEXTURE2D_
