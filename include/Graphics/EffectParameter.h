/********************************************************
 *	EffectParameter.h									*
 *														*
 *	XFX::Graphics::EffectParameter definition file		*
 *	Copyright (c) XFX Team. All Rights Reserved			*
 ********************************************************/
#ifndef _XFX_GRAPHICS_EFFECTPARAMETER_
#define _XFX_GRAPHICS_EFFECTPARAMETER_

#include <System/Object.h>

namespace XFX
{
	namespace Graphics
	{
		// Represents an Effect parameter.
		class EffectParameter : public Object
		{
		public:
			int	GetType() const;

			bool	GetValueBoolean() const;
			bool*	GetValueBooleanArray(int count) const;
			int		GetValueInt32() const;
			int*	GetValueInt32Array(int count) const;
		};
	}
}

#endif //_XFX_GRAPHICS_EFFECTPARAMETER_
