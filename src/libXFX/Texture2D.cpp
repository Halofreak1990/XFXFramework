// Copyright (C) XFX Team
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
#include <Graphics/GraphicsDevice.h>
#include <Graphics/Texture2D.h>
#include <Rectangle.h>
#include <System/FrameworkResources.h>

#include <sassert.h>

using namespace XFX;

namespace XFX
{
	namespace Graphics
	{
		SurfaceFormat_t Texture2D::Format() const
		{
			return _surfaceFormat;
		}
		
		Texture2D::Texture2D(GraphicsDevice * const graphicsDevice, const int width, const int height)
			: textureData(new uint[width*height]), Height(height), Width(width)
		{
			textureId = -1;
			this->graphicsDevice = graphicsDevice;
			this->graphicsDevice->getTextures().textures.Add(this);
			_surfaceFormat = SurfaceFormat::Color;
		}

		Texture2D::Texture2D(GraphicsDevice * const graphicsDevice, const int width, const int height, bool mipmap, const SurfaceFormat_t format)
			: textureData(new uint[width*height]), Height(height), Width(width)
		{
			// TODO: see if there are more supported surfaceformats (likely)
			sassert(format == SurfaceFormat::Color, "Invalid surface format. Valid SurfaceFormats are: Color");

			this->graphicsDevice = graphicsDevice;
			this->graphicsDevice->getTextures().textures.Add(this);
			_surfaceFormat = format;
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

				delete[] textureData;

				if (graphicsDevice->getTextures().textures.Contains(this))
					graphicsDevice->getTextures().textures.Remove(this);
			}
			_isDisposed = true;
		}

		int Texture2D::GetType() const
		{
			// TODO: implement
		}

		void Texture2D::GetData(uint data[], const int startIndex, const int elementCount) const
		{
			sassert(data != null, FrameworkResources::ArgumentNull_Generic);

			sassert(elementCount < (Width * Height), "");

			uint valueMask;

			switch(_surfaceFormat)
			{
			case SurfaceFormat::Color:
				valueMask = 0xFFFFFFFF;
				break;
				// TODO: see if there are more values
			default:
				break;
			}

			for (int i = startIndex, j = 0; i < startIndex + elementCount; i++, j++)
			{
				data[i] = (textureData[j] & valueMask);
			}
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
 		
 		void Texture2D::SetData(uint data[], const int startIndex, const int elementCount, const SetDataOptions_t options) 
 		{ 
			sassert(data != null, FrameworkResources::ArgumentNull_Buffer);

			sassert(elementCount <= Width * Height, "elementCount is larger than the texture size");

			uint dataMask;
			switch(_surfaceFormat)
			{
			case SurfaceFormat::Color:
				dataMask = 0;
				break;
				// TODO: see if there are more values
			default:
				break;
			}

			for (int i = 0, j = startIndex; i < elementCount; i++, j++)
			{
				textureData[i] = (data[j] | dataMask);
			}
 		}

		bool Texture2D::operator ==(const Texture2D& right) const
		{
			return Object::ReferenceEquals(*this, right);
		}

		bool Texture2D::operator !=(const Texture2D& right) const
		{
			return !Object::ReferenceEquals(*this, right);
		}
	}
}
