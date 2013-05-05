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

#include <Matrix.h>
#include <Vector3.h>
#include <Graphics/BasicEffect.h>
#include <Graphics/DirectionalLight.h>

namespace XFX
{
	namespace Graphics
	{
		DirectionalLight* BasicEffect::getDirectionalLight0() const
		{
		}

		DirectionalLight* BasicEffect::getDirectionalLight1() const
		{
		}

		DirectionalLight* BasicEffect::getDirectionalLight2() const
		{
		}

		BasicEffect::BasicEffect(BasicEffect const * const cloneSource)
			: Effect(cloneSource),
			dirtyFlags(-1),
			Alpha(cloneSource->Alpha), AmbientLightColor(cloneSource->AmbientLightColor), DiffuseColor(cloneSource->DiffuseColor),
			EmissiveColor(cloneSource->EmissiveColor), FogColor(cloneSource->FogColor), FogEnabled(cloneSource->FogEnabled),
			FogEnd(1), FogStart(cloneSource->FogStart), LightingEnabled(cloneSource->LightingEnabled),
			PreferPerPixelLighting(cloneSource->PreferPerPixelLighting), Projection(cloneSource->Projection), SpecularColor(cloneSource->SpecularColor),
			SpecularPower(cloneSource->SpecularPower), Texture(cloneSource->Texture), TextureEnabled(cloneSource->TextureEnabled),
			VertexColorEnabled(cloneSource->VertexColorEnabled), View(cloneSource->View), World(cloneSource->World)
		{
		}

		BasicEffect::BasicEffect(GraphicsDevice * const device)
			: Effect(device, null), // TODO: replace null by byte array of actual basic effect shader code
			dirtyFlags(-1),
			Alpha(1), AmbientLightColor(Vector3::Zero), DiffuseColor(Vector3::One),
			EmissiveColor(Vector3::Zero), FogEnabled(false), FogEnd(1.0f),
			Projection(Matrix::Identity), SpecularColor(Vector3::One), SpecularPower(16.0f),
			View(Matrix::Identity), World(Matrix::Identity)
		{
		}

		BasicEffect::~BasicEffect()
		{
		}

		Effect* BasicEffect::Clone() const
		{
			return new BasicEffect(this);
		}

		void BasicEffect::EnableDefaultLighting()
		{
			LightingEnabled = true;
		}

		int BasicEffect::GetType() const
		{
			// TODO: implement
		}

		void BasicEffect::OnApply()
		{
		}
	}
}
