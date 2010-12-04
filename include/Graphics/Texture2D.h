/********************************************************
 *	Texture2D.h											*
 *														*
 *	XFX Texture2D definition file						*
 *	Copyright © XFX Team. All Rights Reserved			*
 ********************************************************/
#ifndef _TEXTURE2D_
#define _TEXTURE2D_

#include "Texture.h"
#include <System/IO/Stream.h>

using namespace System; 
using namespace System::IO;

namespace XFX
{
	class Rectangle;
	
	namespace Graphics
	{
		class Texture2D : Texture
		{
		private:
			GraphicsDevice device;
 			int _height; // The height of the texture before resizing it 
 			bool _isDisposed; // True when the texture has been disposed 
 			int _numberOfLevels; // The number of mip levels for the texture 
 			TextureUsage_t _textureUsage; 
 			SurfaceFormat_t _surfaceFormat; // The colour format of the texture 
 			int _width; // the width of the texture before resizing it
 			int textureId; // The reference ID of the texture in OpenGL memory 
 			int imageId;
 				
 			Texture2D(GraphicsDevice graphicsDevice);
 			void Load(byte buffer[]);
 			
 		protected:
 			void Dispose(bool disposing);
 			
 		public:
 			SurfaceFormat_t Format();
 			int Height();
 			TextureUsage_t TextureUsage_();
 			int Width();
 			
 			Texture2D(GraphicsDevice graphicsDevice, int width, int height);
 			Texture2D(GraphicsDevice graphicsDevice, int width, int height, int numberLevels, TextureUsage_t usage, SurfaceFormat_t format);
 				
 			static Texture2D FromFile(GraphicsDevice graphicsDevice, Stream textureStream);
 			static Texture2D FromFile(GraphicsDevice graphicsDevice, Stream textureStream, TextureCreationParameters creationParameters);
 			static Texture2D FromFile(GraphicsDevice graphicsDevice, Stream textureStream, int numberBytes);
 			static Texture2D FromFile(GraphicsDevice graphicsDevice, Stream textureStream, int numberBytes, TextureCreationParameters creationParameters);
 			static Texture2D FromFile(GraphicsDevice graphicsDevice, char* filename);
 			static Texture2D FromFile(GraphicsDevice graphicsDevice, char* filename, TextureCreationParameters creationParameters);
 			static Texture2D FromFile(GraphicsDevice graphicsDevice, char* filename, int width, int height);

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

#endif //_TEXTURE2D_
