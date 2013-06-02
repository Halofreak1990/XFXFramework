/*****************************************************************************
 *	BasicEffect.h															 *
 *																			 *
 *	XFX::Graphics::BasicEffect definition file  							 *
 *	Copyright (c) XFX Team. All Rights Reserved 							 *
 *****************************************************************************/
#ifndef _XFX_GRAPHICS_BASICEFFECT_
#define _XFX_GRAPHICS_BASICEFFECT_

#include <Graphics/Effect.h>
#include <Matrix.h>
#include <Vector3.h>

namespace XFX
{
	namespace Graphics
	{
		class DirectionalLight;
		class GraphicsDevice;
		class Texture2D;

		// Contains a basic rendering effect.
		class BasicEffect : public Effect
		{
		private:
			int dirtyFlags;

		protected:
			BasicEffect(BasicEffect const * const cloneSource);
			void OnApply();

		public:
			float Alpha;
			Vector3 AmbientLightColor;
			Vector3 DiffuseColor;
			DirectionalLight* getDirectionalLight0() const;
			DirectionalLight* getDirectionalLight1() const;
			DirectionalLight* getDirectionalLight2() const;
			Vector3 EmissiveColor;
			Vector3 FogColor;
			bool FogEnabled;
			float FogEnd;
			float FogStart;
			bool LightingEnabled;
			bool PreferPerPixelLighting;
			Matrix Projection;
			Vector3 SpecularColor;
			float SpecularPower;
			Texture2D* Texture;
			bool TextureEnabled;
			bool VertexColorEnabled;
			Matrix View;
			Matrix World;

			BasicEffect(GraphicsDevice * const device);
			~BasicEffect();

			Effect* Clone() const;
			void EnableDefaultLighting();
			int GetType() const;
		};
	}
}

#endif //_XFX_GRAPHICS_BASICEFFECT_
