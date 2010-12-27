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
		/// <summary>
		/// Describes the display mode.
		/// </summary>
		struct DisplayMode
		{
		public:
			float AspectRatio();
			int Height;
			SurfaceFormat_t Format;
			int RefreshRate;
			Rectangle TitleSafeArea();
			int Width;
				
			DisplayMode();
			bool Equals(const DisplayMode other);
			int GetHashCode();
			
			bool operator!=(const DisplayMode other);
			bool operator==(const DisplayMode other);
		};
	}
}

#endif //_XFX_GRAPHICS_DISPLAYMODE_
