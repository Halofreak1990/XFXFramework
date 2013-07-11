/*****************************************************************************
 *	Effect.h																 *
 *																			 *
 *	XFX::Graphics::Effect definition file									 *
 *	Copyright (c) XFX Team. All Rights Reserved 							 *
 *****************************************************************************/
#ifndef _XFX_GRAPHICS_EFFECT_
#define _XFX_GRAPHICS_EFFECT_

#include <Graphics/EffectParameterCollection.h>
#include <Graphics/EffectTechniqueCollection.h>
#include <Graphics/GraphicsResource.h>

namespace XFX
{
	namespace Graphics
	{
		// Used to set and query effects, and to choose techniques.
		class Effect : public GraphicsResource
		{
		private:
			EffectParameterCollection _parameters;
			EffectTechniqueCollection _techniques;

		protected:
			/**
			 * Creates an instance of this object.
			 *
			 * @param cloneSource
			 * An object to copy.
			 */
			Effect(Effect const * const cloneSource);

			/**
			 * Releases the unmanaged resources used by the Effect and optionally releases the managed resources.
			 */
			void Dispose(bool disposing);
			/**
			 * Applies the effect state just prior to rendering the effect.
			 */
			virtual void OnApply();

		public:
			/**
			 * Gets or sets the active technique.
			 */
			EffectTechnique* CurrentTechnique;
			/**
			 * Gets a collection of parameters used for this effect.
			 */
			EffectParameterCollection& getParameters() const;
			/**
			 * Gets a collection of techniques that are defined for this effect.
			 */
			EffectTechniqueCollection& getTechniques() const;

			/**
			 * Creates an instance of this object.
			 *
			 * @param graphicsDevice
			 * The device.
			 *
			 * @param effectCode
			 * The effect code.
			 */
			Effect(GraphicsDevice * const graphicsDevice, byte effectCode[]);

			/**
			 * Copies data from an existing object to this object.
			 */
			virtual Effect* Clone() const;
			static int GetType();
		};
	}
}

#endif //_XFX_GRAPHICS_EFFECT_
