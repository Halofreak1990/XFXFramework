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

#include <Graphics/TextureCreationParameters.h>

namespace XFX
{
	namespace Graphics
	{
		TextureCreationParameters::TextureCreationParameters(int width, int height, int depth, int mipLevels, SurfaceFormat_t format,
			TextureUsage_t textureUsage, Color colorKey, FilterOptions_t filter, FilterOptions_t mipFilter)
		{
			Width = width;
			Height = height;
			Depth = depth;
			MipLevels = mipLevels;
			Format = format;
			TextureUsage_ = textureUsage;
			ColorKey = colorKey;
			Filter = filter;
			MipFilter = mipFilter;
		}

		TextureCreationParameters::TextureCreationParameters(const TextureCreationParameters &obj)
		{
			Width = obj.Width;
			Height = obj.Height;
			Depth = obj.Depth;
			MipLevels = obj.MipLevels;
			Format = obj.Format;
			TextureUsage_ = obj.TextureUsage_;
			ColorKey = obj.ColorKey;
			Filter = obj.Filter;
			MipFilter = obj.MipFilter;
		}

		TextureCreationParameters::TextureCreationParameters()
		{
			Default = TextureCreationParameters(
				0, 0, 0, 0,
				SurfaceFormat::Unknown,
				TextureUsage::None,
				Color::TransparentBlack,
				(FilterOptions_t)(FilterOptions::Dither | FilterOptions::Triangle),
				FilterOptions::Box);
		}

		bool TextureCreationParameters::Equals(TextureCreationParameters other)
		{
			return ((Width == other.Width) && (Height == other.Height) &&
				(Depth == other.Depth) && (MipLevels == other.MipLevels) &&
				(Format == other.Format) && (ColorKey == other.ColorKey) &&
				(Filter == other.Filter) && (MipFilter == other.MipFilter));
		}

		int TextureCreationParameters::GetHashCode()
		{
			return (Width ^ Height ^ Depth ^ MipLevels ^ Format ^ Filter ^ MipFilter);
		}
		//
		// Operators
		//
		bool TextureCreationParameters::operator !=(TextureCreationParameters other)
		{
			return !Equals(other);
		}

		bool TextureCreationParameters::operator ==(TextureCreationParameters other)
		{
			return Equals(other);
		}
	}
}
