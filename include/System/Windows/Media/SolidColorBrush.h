/*****************************************************************************
 *	SolidColorBrush.h														 *
 *																			 *
 *	System::Windows::Media::SolidColorBrush definition file 				 *
 *	Copyright (c) XFX Team. All rights reserved								 *
 *****************************************************************************/
#ifndef _SYSTEM_WINDOWS_MEDIA_SOLIDCOLORBRUSH_
#define _SYSTEM_WINDOWS_MEDIA_SOLIDCOLORBRUSH_

#include <System/Windows/Media/Brush.h>
#include <System/Windows/Media/Color.h>

namespace System
{
	namespace Windows
	{
		namespace Media
		{
			/**
			 * Paints an area with a solid color.
			 */
			class SolidColorBrush : public Brush
			{
			public:
				System::Windows::Media::Color Color;

				SolidColorBrush();
				SolidColorBrush(const System::Windows::Media::Color color);

				static const Type& GetType();
			};
		}
	}
}

#endif //_SYSTEM_WINDOWS_MEDIA_SOLIDCOLORBRUSH_