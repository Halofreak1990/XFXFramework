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

#include <Graphics/RenderTarget2D.h>
#include <Graphics/Texture2D.h>
#include <sassert.h>

#include "pbkit.h"

namespace XFX
{
	namespace Graphics
	{
		int RenderTarget2D::bufferCount = 0;

		RenderTarget2D::RenderTarget2D(GraphicsDevice * const graphicsDevice, const int width, const int height)
			: Texture2D(graphicsDevice, width, height)
		{
			//! TODO: implement
		}

		RenderTarget2D::RenderTarget2D(GraphicsDevice * const graphicsDevice, const int width, const int height, const bool mipmap, const SurfaceFormat_t preferredFormat, const DepthFormat_t preferredDepthFormat)
			: Texture2D(graphicsDevice, width, height, mipmap, TextureUsage::None, preferredFormat)
		{
			//! TODO: implement
		}

		RenderTarget2D::RenderTarget2D(GraphicsDevice * const graphicsDevice, const int width, const int height, const bool mipmap, const SurfaceFormat_t preferredFormat, const DepthFormat_t preferredDepthFormat, const int multisampleCount, const RenderTargetUsage_t usage)
			: Texture2D(graphicsDevice, width, height, mipmap, TextureUsage::None, preferredFormat)
		{
			//! TODO: implement
		}

		RenderTarget2D::~RenderTarget()
		{
		}

		void RenderTarget2D::Dispose(bool disposing)
		{
		}

		int RenderTarget2D::GetType() const
		{
		}

		void RenderTarget2D::raise_ContentLost(Object * const sender, EventArgs * const e)
		{
			ContentLost(sender, e);
		}

		bool RenderTarget2D::operator !=(const RenderTarget2D& right) const
		{
			return !Object::ReferenceEquals(*this, right);
		}

		bool RenderTarget2D::operator ==(const RenderTarget2D& right) const
		{
			return Object::ReferenceEquals(*this, right);
		}
	}
}
