/********************************************************
 *	DisplayModeCollection.h								*
 *														*
 *	XFX DisplayModeCollection definition file			*
 *	Copyright © XFX Team. All Rights Reserved			*
 ********************************************************/
#ifndef _XFX_GRAPHICS_DISPLAYMODECOLLECTION_
#define _XFX_GRAPHICS_DISPLAYMODECOLLECTION_

#include <System/Types.h>
#include <System/Collections/Generic/List.h>
#include "DisplayMode.h"

using namespace System;
using namespace System::Collections::Generic;

namespace XFX
{
	namespace Graphics
	{
		// Manipulates a collection of DisplayMode structures.
		struct DisplayModeCollection
		{
		private:
			int adapterOrdinal;
			List<DisplayMode> displayModes;
			SurfaceFormat_t currentFormat;
			int count;	

		public:
			DisplayModeCollection();

			bool operator!=(const DisplayModeCollection other) const;
			bool operator==(const DisplayModeCollection other) const;
		};
	}
}

#endif //_XFX_GRAPHICS_DISPLAYMODECOLLECTION_
