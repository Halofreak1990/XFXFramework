/********************************************************
 *	BasicDirectionalLight.h								*
 *														*
 *	BasicDirectionalLight definition file				*
 *	Copyright © XFX Team. All Rights Reserved			*
 ********************************************************/
#ifndef _XFX_GRAPHICS_BASICDIRECTIONALLIGHT_
#define _XFX_GRAPHICS_BASICDIRECTIONALLICHT_

#include <Vector3.h>

namespace XFX
{
	namespace Graphics
	{
		/// <summary>
		/// Provides methods for manipulating the directional lights used by the BasicEffect class.
		/// </summary>
		class BasicDirectionalLight
		{
		public:
			Vector3 DiffuseColor;
			Vector3 Direction;
			bool Enabled;
			Vector3 SpecularColor;
		};
	}
}

#endif //_XFX_GRAPHICS_BASICDIRECTIONALLIGHT_
