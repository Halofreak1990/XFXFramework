/*****************************************************************************
 *	EffectTechnique.h														 *
 *																			 *
 *	XFX::Graphics::EffectTechnique definition file							 *
 *	Copyright (c) XFX Team. All Rights Reserved 							 *
 *****************************************************************************/
#ifndef _XFX_GRAPHICS_EFFECTTECHNIQUE_
#define _XFX_GRAPHICS_EFFECTTECHNIQUE_

#include <Graphics/EffectAnnotationCollection.h>
#include <Graphics/EffectPassCollection.h>
#include <System/String.h>

using namespace System;

namespace XFX
{
	namespace Graphics
	{
		/**
		 * Represents an effect technique.
		 */
		class EffectTechnique
		{
		private:
			EffectAnnotationCollection _annotations;

		public:
			/**
			 * Gets the EffectAnnotation objects associated with this technique.
			 */
			EffectAnnotationCollection& getAnnotations() const;
			/**
			 * Gets the name of this technique.
			 */
			String& getName() const;
			/**
			 * Gets the collection of EffectPass objects this rendering technique requires.
			 */
			EffectPassCollection& getPasses() const;
		};
	}
}

#endif //_XFX_GRAPHICS_EFFECTTECHNIQUE_
