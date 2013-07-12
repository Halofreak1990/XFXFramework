/*****************************************************************************
 *	DisplayModeCollection.h													 *
 *																			 *
 *	XFX::Graphics::DisplayModeCollection class definition file  			 *
 *	Copyright (c) XFX Team. All Rights Reserved 							 *
 *****************************************************************************/
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
		/**
		 * Manipulates a collection of DisplayMode structures.
		 */
		class DisplayModeCollection : IEnumerable<DisplayMode>, Object
		{
		private:
			int adapterOrdinal;
			List<DisplayMode> displayModes;
			SurfaceFormat_t currentFormat;
			int count;	

		public:
			DisplayModeCollection();

			IEnumerator<DisplayMode>* GetEnumerator();
			static const Type& GetType();

			DisplayMode& operator[](const SurfaceFormat_t format) const;
		};
	}
}

#endif //_XFX_GRAPHICS_DISPLAYMODECOLLECTION_
