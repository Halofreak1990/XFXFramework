/*****************************************************************************
 *	Brush.h 																 *
 *																			 *
 *	System::Windows::Media::Brush definition file							 *
 *	Copyright (c) XFX Team. All rights reserved								 *
 *****************************************************************************/
#ifndef _SYSTEM_WINDOWS_MEDIA_BRUSH_
#define _SYSTEM_WINDOWS_MEDIA_BRUSH_

#include <System/Object.h>

namespace System
{
	namespace Windows
	{
		namespace Media
		{
			/**
			 * Defines objects used to paint graphical objects. Classes that derive from System::Windows::Media::Brush describe how the area is painted.
			 */
			class Brush : public Object
			{
			protected:
				Brush();

			public:
				int Opacity;

				virtual ~Brush();

				static const Type& GetType();
			};
		}
	}
}

#endif //_SYSTEM_WINDOWS_MEDIA_BRUSH_
