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
 			int _height; // The height of the texture before resizing it 
 			bool _isDisposed; // True when the texture has been disposed 
 			int _numberOfLevels; // The number of mip levels for the texture 
 			TextureUsage_t _textureUsage; 
 			SurfaceFormat_t _surfaceFormat; // The colour format of the texture 
 			int _width; // the width of the texture before resizing it
 			int textureId; // The reference ID of the texture in OpenGL memory 
 			int imageId;
 				
 			void Load(byte buffer[]);
			Texture2D(GraphicsDevice* graphicsDevice);
 			
 		protected:
 			void Dispose(bool disposing);
 			
 		public:
 			SurfaceFormat_t Format();
 			int getHeight();
 			TextureUsage_t TextureUsage();
 			int getWidth();
 			
			Texture2D();
 			Texture2D(GraphicsDevice* graphicsDevice, int width, int height);
 			Texture2D(GraphicsDevice* graphicsDevice, int width, int height, int numberLevels, TextureUsage_t usage, SurfaceFormat_t format);
			Texture2D(const Texture2D &obj); // Copy constructor
 				
 			static Texture2D FromFile(GraphicsDevice* graphicsDevice, Stream* textureStream);
 			static Texture2D FromFile(GraphicsDevice* graphicsDevice, Stream* textureStream, TextureCreationParameters creationParameters);
 			static Texture2D FromFile(GraphicsDevice* graphicsDevice, Stream* textureStream, int numberBytes);
 			static Texture2D FromFile(GraphicsDevice* graphicsDevice, Stream* textureStream, int numberBytes, TextureCreationParameters creationParameters);
 			static Texture2D FromFile(GraphicsDevice* graphicsDevice, char* filename);
 			static Texture2D FromFile(GraphicsDevice* graphicsDevice, char* filename, TextureCreationParameters creationParameters);
 			static Texture2D FromFile(GraphicsDevice* graphicsDevice, char* filename, int width, int height);

 			template <class T>
 			void GetData(T data[]);
			template <class T>
 			void GetData(T data[], int startIndex, int elementCount);
			template <class T>
 			void GetData(int level, Rectangle rect, T data[], int startIndex, int elementCount);
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
