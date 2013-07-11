/*****************************************************************************
 *	AlphaTestEffect.h														 *
 *																			 *
 *	XFX::Graphics::AlphaTestEffect definition file							 *
 *	Copyright (c) XFX Team. All Rights Reserved 							 *
 *****************************************************************************/
#ifndef _XFX_GRAPHICS_ALPHATESTEFFECT_
#define _XFX_GRAPHICS_ALPHATESTEFFECT_

#include "Effect.h"
#include <Matrix.h>
#include <Vector3.h>

using namespace System;

namespace XFX
{
	namespace Graphics
	{
		class Texture2D;

		/**
		 * Contains a configurable effect that supports alpha testing.
		 */
		class AlphaTestEffect : public Effect
		{
		private:
			byte effectCode[];

		protected:
			AlphaTestEffect(AlphaTestEffect const * const cloneSource);

			void OnApply();

		public:
			float Alpha;
			CompareFunction_t AlphaFunction;
			Vector3 DiffuseColor;
			Vector3 FogColor;
			bool FogEnabled;
			float FogEnd;
			float FogStart;
			Matrix Projection;
			int ReferenceAlpha;
			Texture2D* Texture;
			bool VertexColorEnabled;
			Matrix View;
			Matrix World;

			AlphaTestEffect(GraphicsDevice * const device);

			Effect* Clone() const;
			int GetType() const;
		};
	}
}

#endif //_XFX_GRAPHICS_ALPHATESTEFFECT_
