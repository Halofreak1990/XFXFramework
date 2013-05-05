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

#include <Graphics/TextureInformation.h>
#include <stdio.h>

namespace XFX
{
	namespace Graphics
	{
		TextureInformation::TextureInformation(int width, int height, int depth, int mipLevels, SurfaceFormat_t format)
		{
			Width = width;
			Height = height;
			Depth = depth;
			MipLevels = mipLevels;
			Format = format;
			ImageFormat = ImageFileFormat::Jpg;
			ResourceType_ = ResourceType::Texture2D;
		}

		TextureInformation::TextureInformation(const TextureInformation &obj)
		{
			Width = obj.Width;
			Height = obj.Height;
			Depth = obj.Depth;
			Format = obj.Format;
			MipLevels = obj.MipLevels;
			ResourceType_ = obj.ResourceType;
			ImageFormat = obj.ImageFormat;
		}

		TextureInformation::TextureInformation()
		{
			ImageFormat = ImageFileFormat::Jpg;
			ResourceType_ = ResourceType::Texture2D;
		}

		bool TextureInformation::Equals(TextureInformation other)
		{
			return ((Width = other.Width) && (Height == other.Height) &&
				(Depth == other.Depth) && (Format == other.Format) &&
				(ImageFormat == other.ImageFormat) && (MipLevels == other.MipLevels) &&
				(ResourceType_ == other.ResourceType_));
		}

		int TextureInformation::GetHashCode()
		{
			return (Width ^ Height ^ Depth ^ Format ^ MipLevels ^ ImageFormat ^ ResourceType_);
		}

		char* TextureInformation::ToString()
		{
			char* buf;
			sprintf(buf, "{Width:%d Height:%d Format:%d Depth:%d MipLevels:%d}", Width, Height, Format, Depth, MipLevels);
			return buf;
		}
		//
		// Operators
		//
		bool TextureInformation::operator!=(TextureInformation other)
		{
			return !Equals(other);
		}

		bool TextureInformation::operator==(TextureInformation other)
		{
			return Equals(other);
		}
	}
}
