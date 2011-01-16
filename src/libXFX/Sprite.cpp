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

#include <Graphics/Sprite.h>

namespace XFX
{
	namespace Graphics
	{
		Sprite::Sprite(Texture2D texture, Rectangle sourceRectangle, Rectangle destinationRectangle, Color color, float rotation, Vector2 origin, SpriteEffects_t effects, float layerDepth)
		{
			this->texture = texture;
			this->sourceRectangle = sourceRectangle;
			this->destinationRectangle = destinationRectangle;
			this->color = color;
			this->rotation = rotation;
			this->origin = origin;
			this->effects = effects;
			this->layerDepth = layerDepth;
		}

		Texture2D Sprite::Texture()
		{
			return texture;
		}

		Rectangle Sprite::SourceRectangle()
		{
			return sourceRectangle;
		}

		Rectangle Sprite::DestinationRectangle()
		{
			return destinationRectangle;
		}

		Color Sprite::Color_()
		{
			return color;
		}

		float Sprite::Rotation()
		{
			return rotation;
		}

		Vector2 Sprite::Origin()
		{
			return origin;
		}

		SpriteEffects_t Sprite::Effects()
		{
			return effects;
		}

		float Sprite::LayerDepth()
		{
			return layerDepth;
		}
	}
}
