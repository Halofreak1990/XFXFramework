/*****************************************************************************
 *	Effect.h																 *
 *																			 *
 *	XFX::Graphics::Effect definition file									 *
 *	Copyright (c) XFX Team. All Rights Reserved 							 *
 *****************************************************************************/
#ifndef _XFX_GRAPHICS_EFFECT_
#define _XFX_GRAPHICS_EFFECT_

#include <Graphics/GraphicsResource.h>

namespace XFX
{
	namespace Graphics
	{
		// Used to set and query effects, and to choose techniques.
		class Effect : public GraphicsResource
		{
		protected:
			Effect(Effect const * const cloneSource);

			void Dispose(bool disposing);
			virtual void OnApply();

		public:
			Effect(GraphicsDevice * const graphicsDevice, byte effectCode[]);

			virtual Effect* Clone() const;
			int GetType() const;
		};
	}
}

#endif //_XFX_GRAPHICS_EFFECT_
