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
		/// <summary>
		/// Manipulates a collection of DisplayMode structures.
		/// </summaryy>
		struct DisplayModeCollection
		{
		private:
			int adapterOrdinal;
			List<DisplayMode> displayModes;
			SurfaceFormat_t currentFormat;
			int count;	

		public:
			DisplayModeCollection();

			bool operator!=(DisplayModeCollection other);
			bool operator==(DisplayModeCollection other);
		};
	}
}

#endif //_XFX_GRAPHICS_DISPLAYMODECOLLECTION_
