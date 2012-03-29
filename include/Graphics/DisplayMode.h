/********************************************************
 *	DisplayMode.h										*
 *														*
 *	XFX DisplayMode structure definition file			*
 *	Copyright © XFX Team. All Rights Reserved			*
 ********************************************************/
#ifndef _XFX_GRAPHICS_DISPLAYMODE_
#define _XFX_GRAPHICS_DISPLAYMODE_

#include "Enums.h"

namespace XFX
{
	struct Rectangle;
	
	namespace Graphics
	{
		// Describes the display mode.
		struct DisplayMode
		{
			float AspectRatio() const;
			int Height;
			SurfaceFormat_t Format;
			int RefreshRate;
			Rectangle TitleSafeArea() const;
			int Width;
				
			DisplayMode();
			bool Equals(const DisplayMode other) const;
			int GetHashCode() const;
			
			bool operator!=(const DisplayMode other) const;
			bool operator==(const DisplayMode other) const;
		};
	}
}

#endif //_XFX_GRAPHICS_DISPLAYMODE_
