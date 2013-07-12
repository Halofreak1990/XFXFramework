/*****************************************************************************
 *	DisplayMode.h															 *
 *																			 *
 *	XFX::Graphics::DisplayMode structure definition file					 *
 *	Copyright (c) XFX Team. All Rights Reserved 							 *
 *****************************************************************************/
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
		/**
		 * Describes the display mode.
		 */
		struct DisplayMode : Object
		{
			float getAspectRatio() const;
			int Height;
			SurfaceFormat_t Format;
			int RefreshRate;
			Rectangle getTitleSafeArea() const;
			int Width;
				
			DisplayMode();

			bool Equals(Object const * const obj) const;
			int GetHashCode() const;
			static const Type& GetType();
			
			bool operator!=(const DisplayMode& other) const;
			bool operator==(const DisplayMode& other) const;
		};
	}
}

#endif //_XFX_GRAPHICS_DISPLAYMODE_
