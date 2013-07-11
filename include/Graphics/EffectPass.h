/*****************************************************************************
 *	EffectPass.h															 *
 *																			 *
 *	XFX::Graphics::EffectPass definition file								 *
 *	Copyright (c) XFX Team. All Rights Reserved 							 *
 *****************************************************************************/
#ifndef _XFX_GRAPHICS_EFFECTPASS_
#define _XFX_GRAPHICS_EFFECTPASS_

#include <Graphics/EffectAnnotationCollection.h>
#include <System/String.h>

using namespace System;

namespace XFX
{
	namespace Graphics
	{
		/**
		 * Contains rendering state for drawing with an effect; an effect can contain one or more passes.
		 */
		class EffectPass
		{
		public:
			/**
			 * Gets the set of EffectAnnotation objects for this EffectPass.
			 */
			EffectAnnotationCollection& getAnnotations() const;
			/**
			 * Gets the name of this pass.
			 */
			String& getName();

			/**
			 * Begins this pass.
			 */
			void Apply();
		};
	}
}

#endif //_XFX_GRAPHICS_EFFECTPASS_
