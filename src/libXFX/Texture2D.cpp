// Copyright (C) 2010-2012, XFX Team
// All rights reserved.
// 
// Redistribution and use in source and binary forms, with or without 
// modification, are permitted provided that the following conditions are met:
// 
//     * Redistributions of source code must retain the above copyright 
//       notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above copyright 
//       notice, this list of conditions and the following disclaimer in the 
//       documentation and/or other materials provided with the distribution.
//     * Neither the name of the copyright holder nor the names of any 
//       contributors may be used to endorse or promote products derived from 
//       this software without specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE 
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE 
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR 
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF 
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS 
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN 
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE 
// POSSIBILITY OF SUCH DAMAGE.

#include <Graphics/Color.h>
#include <Graphics/DepthStencilBuffer.h>
#include <Graphics/GraphicsDevice.h>
#include <Graphics/Texture2D.h>
#include <Rectangle.h>

using namespace XFX;

namespace XFX
{
	namespace Graphics
	{
		SurfaceFormat_t Texture2D::Format() const
		{
			return _surfaceFormat;
		}
		
		TextureUsage_t Texture2D::TextureUsage() const
		{
			return _textureUsage;
		}
		
		Texture2D::Texture2D(GraphicsDevice* graphicsDevice)
			: Height(0), Width(0)
		{
			textureId = -1;
			this->graphicsDevice = graphicsDevice;
		}
		
		Texture2D::Texture2D(GraphicsDevice* graphicsDevice, const int width, const int height)
			: Height(height), Width(width)
		{
			textureId = -1;
			this->graphicsDevice = graphicsDevice;
		}
		
		Texture2D::Texture2D(GraphicsDevice* graphicsDevice, const int width, const int height, const int numberLevels, const TextureUsage_t usage, const SurfaceFormat_t format)
			: Height(height), Width(width)
		{
			textureId = -1;
			this->graphicsDevice = graphicsDevice;
			_numberOfLevels = numberLevels;
			_textureUsage = usage;
			_surfaceFormat = format;
		}

		Texture2D::Texture2D(const Texture2D &obj)
			: Height(obj.Height), Width(obj.Width)
		{
			textureId = obj.textureId;
			this->graphicsDevice = obj.graphicsDevice;
			_numberOfLevels = obj._numberOfLevels;
			_textureUsage = obj._textureUsage;
			_surfaceFormat = obj._surfaceFormat;
		}
		
		void Texture2D::Dispose(bool disposing)
		{
			if(!_isDisposed)
			{
				/*try
				{
					//glDeleteTextures(1, int[] { textureId });
				}
				catch(Exception)
				{
					
				}
				if(device.Textures().textures.Contains(this))
					device.Textures().textures.Remove(this);*/
			}
			_isDisposed = true;
		}
		
		void Texture2D::Load(byte buffer[])
		{
			/*imageId = Il::ilGenImage(); 
            Il::ilBindImage(imageId); 
            Il::ilLoadL(Il::IL_JPG, buffer, buffer.Length); 
                          
            int[] texture = int[1]; 
            glGenTextures(1, texture); 
            textureId = texture[0]; 
            glBindTexture(GL_TEXTURE_2D, textureId);                       
            glTexImage2D(GL_TEXTURE_2D, 0, Il::ilGetInteger(Il::IL_IMAGE_BYTES_PER_PIXEL), _width, _height, 0, GL_RGBA, GL_UNSIGNED_BYTE, Il::ilGetData());                   
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);*/
		}
		
		template <class T>
		void Texture2D::SetData(T data[]) 
 		{ 
 			Rectangle rect; 
 			SetData<T>(0, rect, data, 0, data.Length, SetDataOptions::None); 
 		}
 		
		template <class T>
 		void Texture2D::SetData(T data[], int startIndex, int elementCount, SetDataOptions_t options) 
 		{ 
 			Rectangle rect; 
 			SetData<T>(0, rect, data, startIndex, elementCount, options); 
 		} 
		
		template <class T>
		void Texture2D::SetData(int level, Rectangle rect, T data[], int startIndex, int elementCount, SetDataOptions_t options) 
 		{ 
 			if (textureId == -1 || options == SetDataOptions::NoOverwrite) 
 			{ 
				/*int[] texture = new int[1];
 				glGenTextures(1, texture); 
 				textureId = texture[0];*/
 			} 
 			//glBindTexture(GL_TEXTURE_2D, textureId);

 			switch (_surfaceFormat) 
 			{ 
 				case SurfaceFormat::Color:
 					//glTexImage2D(GL_TEXTURE_2D, 0, 4, _width, _height, 0, GL_BGRA, GL_UNSIGNED_BYTE, data); 
 					break; 
 				case SurfaceFormat::Dxt1: 
 					//glCompressedTexImage2D(GL_TEXTURE_2D, 0, GL_COMPRESSED_RGBA_S3TC_DXT1_EXT, _width, _height, 0, elementCount, data);
					break; 
 				case SurfaceFormat::Dxt3:
 					//glCompressedTexImage2D(GL_TEXTURE_2D, 0, GL_COMPRESSED_RGBA_S3TC_DXT3_EXT, _width, _height, 0, elementCount, data);
 					break; 
 				case SurfaceFormat::Dxt5:
 					//glCompressedTexImage2D(GL_TEXTURE_2D, 0, GL_COMPRESSED_RGBA_S3TC_DXT5_EXT, _width, _height, 0, elementCount, data);
 					break; 
 			}
 			/*glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
 			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);*/
 		} 
	}
}
