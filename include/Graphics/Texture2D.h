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
		class Texture2D : public Texture, virtual Object
		{
		private:
			GraphicsDevice* device;
 			bool _isDisposed; // True when the texture has been disposed 
 			int _numberOfLevels; // The number of mip levels for the texture 
 			TextureUsage_t _textureUsage; 
 			SurfaceFormat_t _surfaceFormat; // The colour format of the texture 
 			int textureId; // The reference ID of the texture in OpenGL memory 
 			int imageId;
 				
 			void Load(byte buffer[]);
			Texture2D(GraphicsDevice* graphicsDevice);
 			
 		protected:
 			void Dispose(bool disposing);
 			
 		public:
 			SurfaceFormat_t Format() const;
 			const int Height;
 			TextureUsage_t TextureUsage() const;
 			const int Width;
 			
 			Texture2D(GraphicsDevice* graphicsDevice, const int width, const int height);
 			Texture2D(GraphicsDevice* graphicsDevice, const int width, const int height, const int numberLevels, const TextureUsage_t usage, const SurfaceFormat_t format);
			Texture2D(const Texture2D &obj); // Copy constructor
 				
 			static Texture2D FromFile(GraphicsDevice* graphicsDevice, Stream* textureStream);
 			static Texture2D FromFile(GraphicsDevice* graphicsDevice, Stream* textureStream, const TextureCreationParameters& creationParameters);
 			static Texture2D FromFile(GraphicsDevice* graphicsDevice, Stream* textureStream, const int numberBytes);
 			static Texture2D FromFile(GraphicsDevice* graphicsDevice, Stream* textureStream, const int numberBytes, const TextureCreationParameters& creationParameters);
 			static Texture2D FromFile(GraphicsDevice* graphicsDevice, const char* filename);
 			static Texture2D FromFile(GraphicsDevice* graphicsDevice, const char* filename, const TextureCreationParameters& creationParameters);
 			static Texture2D FromFile(GraphicsDevice* graphicsDevice, const char* filename, const int width, const int height);

 			template <class T>
 			void GetData(T data[]) const;
			template <class T>
 			void GetData(T data[], int startIndex, int elementCount) const;
			template <class T>
 			void GetData(int level, Rectangle rect, T data[], int startIndex, int elementCount) const;
			template <class T>
 			void SetData(T data[]);
			template <class T>
 			void SetData(T data[], int startIndex, int elementCount, SetDataOptions_t options);
			template <class T>
 			void SetData(int level, Rectangle rect, T data[], int startIndex, int elementCount, SetDataOptions_t options);
		};
	}
}

#endif //_XFX_GRAPHICS_TEXTURE2D_
