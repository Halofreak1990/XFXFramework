/********************************************************
 *	DisplayMode.h										*
 *														*
 *	XFX DisplayMode structure definition file			*
 *	Copyright © XFX Team. All Rights Reserved			*
 ********************************************************/
#ifndef _XFX_GRAPHICS_DISPLAYMODE_
#define _XFX_GRAPHICS_DISPLAYMODE_

#include "Enums.h"
#include <System/Object.h>

using namespace System;

namespace XFX
{
	struct Rectangle;
	
	namespace Graphics
	{
		// Describes the display mode.
		struct DisplayMode : Object
		{
			float getAspectRatio() const;
			int Height;
			SurfaceFormat_t Format;
			int RefreshRate;
			Rectangle getTitleSafeArea() const;
			int Width;
				
			DisplayMode();
			bool Equals(const Object* obj) const;
			int GetHashCode() const;
			int GetType() const;
			
			bool operator!=(const DisplayMode& other) const;
			bool operator==(const DisplayMode& other) const;
		};
	}
}

#endif //_XFX_GRAPHICS_DISPLAYMODE_
