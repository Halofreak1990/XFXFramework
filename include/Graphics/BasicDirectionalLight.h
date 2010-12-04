/********************************************************
 *	BasicDirectionalLight.h								*
 *														*
 *	BasicDirectionalLight definition file				*
 *	Copyright © XFX Team. All Rights Reserved			*
 ********************************************************/
#ifndef _BASICDIRECTIONALLIGHT_H_
#define _BASICDIRECTIONALLICHT_H_

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
			int Enabled;
			Vector3 SpecularColor;
		};
	}
}

#endif //_BASICDIRECTIONALLIGHT_H_
