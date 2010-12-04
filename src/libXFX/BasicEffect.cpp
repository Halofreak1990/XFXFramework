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

#include <BasicEffect.h>

namespace XFX
{
	namespace Graphics
	{
		BasicEffect::BasicEffect(GraphicsDevice &device, BasicEffect &clone)
			: Effect(device, clone)
		{
		}
		BasicEffect::BasicEffect(GraphicsDevice &device, EffectPool &effectPool)
		{
		}

		Effect BasicEffact::Clone(GraphicsDevice &device)
		{
			BasicEffect effect = BasicEffect(device, *this);
			return effect;
		}

		void BasicEffect::EnableDefaultLighting()
		{
			LightingEnabled = true;
			AmbientLightColor = Vector3(0.05333332f, 0.09882354f, 0.1819608f);
			Vector3 color = Vector3(1f, 0.9607844f, 0.8078432f);
			DirectionalLight0.DiffuseColor = color;
			DirectionalLight0.Direction = Vector3(-0.5265408f, -0.5735765f, -0.6275069f);
			DirectionalLight0.SpecularColor = color;
			DirectionalLight0.Enabled = true;
			DirectionalLight1.DiffuseColor = Vector3(0.9647059f, 0.7607844f, 0.4078432f);
			DirectionalLight1.Direction = Vector3(0.7198464f, 0.3420201f, 0.6040227f);
			DirectionalLight1.SpecularColor = Vector3.Zero;
			DirectionalLight1.Enabled = true;
			color = Vector3(0.3231373f, 0.3607844f, 0.3937255f);
			DirectionalLight2.DiffuseColor = color;
			DirectionalLight2.Direction = Vector3(0.4545195f, -0.7660444f, 0.4545195f);
			DirectionalLight2.SpecularColor = color;
			DirectionalLight2.Enabled = true;
		}
	}
}
