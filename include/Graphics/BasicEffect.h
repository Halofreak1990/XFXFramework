/********************************************************
 *	BasicEffect.h										*
 *														*
 *	BasicEffect definition file							*
 *	Copyright © XFX Team. All Rights Reserved			*
 ********************************************************/
#ifndef _BASICEFFECT_H_
#define _BASICEFFECT_H_

#include "BasicDirectionalLight.h"
#include "Effect.h"
//#include "GraphicsDevice.h"
#include <Matrix.h>
#include "Texture2D.h"
#include <Vector3.h>

namespace XFX
{
	namespace Graphics
	{
		/// <summary>
		/// Represents shader model 1.1 Effect that has optional support for vertex colors, texturing, and lighting.
		/// </summary>
		class BasicEffect : public Effect
		{
		protected:
			BasicEffect(GraphicsDevice device, BasicEffect clone);
			
		public:
			float Alpha;
			Vector3 AmbientLightColor;
			Vector3 DiffuseColor;
			BasicDirectionalLight DirectionalLight0();
			BasicDirectionalLight DirectionalLight1();
			BasicDirectionalLight DirectionalLight2();
			Vector3 EmissiveColor;
			Vector3 FogColor;
			int FogEnabled;
			float FogEnd;
			float FogStart;
			int LightingEnabled;
			int PreferPerPixelLighting;
			Matrix Projection;
			Vector3 SpecularColor;
			float SpecularPower;
			Texture2D Texture_;
			int TextureEnabled;
			int VertexColorEnabled;
			Matrix View;
			Matrix World;
		
			BasicEffect(GraphicsDevice device, EffectPool effectPool);
			
			Effect Clone(GraphicsDevice device);
			void EnableDefaultLighting();
		};
	}
}

#endif //_BASICEFFECT_H_
