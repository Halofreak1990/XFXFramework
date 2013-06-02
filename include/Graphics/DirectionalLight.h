/*****************************************************************************
 *	DirectionalLight.h														 *
 *																			 *
 *	XFX::Graphics::DirectionalLight definition file 						 *
 *	Copyright (c) XFX Team. All Rights Reserved 							 *
 *****************************************************************************/
#ifndef _XFX_GRAPHICS_DIRECTIONALLIGHT_
#define _XFX_GRAPHICS_DIRECTIONALLIGHT_

#include <System/Object.h>
#include "EffectParameter.h"
#include <Vector3.h>

using namespace System;

namespace XFX
{
	namespace Graphics
	{
		// Creates a DirectionalLight object.
		class DirectionalLight : public Object
		{
		public:
			Vector3 DiffuseColor;
			Vector3 Direction;
			bool Enabled;
			Vector3 SpecularColor;

			DirectionalLight(EffectParameter * const directionParameter, EffectParameter * const diffuseColorParameter, EffectParameter * const specularColorParameter, DirectionalLight const * const cloneSource);

			int GetType() const;
		};
	}
}

#endif //_XFX_GRAPHICS_DIRECTIONALLIGHT_
